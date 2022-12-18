#include "VulnerableWebApplicationClientThread.h"
#include "GenericApplicationMessage_m.h"
#include "TCPSocket.h"
#include <iostream>

/**
 * @brief A client thread implements the endpoint of a client/server connection.
 *
 * The client opens a socket and starts the communication by sending the first request.
 * Such a request contains all data necessary for the server to generate a reply.
 * After a maximum number of requests has been sent, the socket is closed and the
 * thread removed.
 *
 * @class VulnerableWebApplicationClientThread
 */

/// Thread States
/// @{
#define NOT_SET 0
#define WAITING 1
#define CONNECTED 2
#define DISCONNECTED 3
#define FINISH 4
/// @}

VulnerableWebApplicationClientThread::VulnerableWebApplicationClientThread( TargetInfo &i)
{
	curTarget = i;
	selfMsg = NULL;
}

VulnerableWebApplicationClientThread::~VulnerableWebApplicationClientThread()
{
	if (selfMsg)
	{
		if (selfMsg->isScheduled())
			cancelEvent(selfMsg);
		delete selfMsg;
	}
}

/**
 * Sets timer for starting the new communication.
 */
void VulnerableWebApplicationClientThread::init(VulnerableWebApplication *owner, TCPSocket *sock)
{

	VulnerableWebApplicationThreadBase::init(owner, sock);
	threadState = WAITING;
	selfMsg = new cMessage("threadtimer");
	scheduleAt(simTime() + SELF_CALL_DELAY, selfMsg);

}
/**
 * Manage TCP state transitions
 */
void VulnerableWebApplicationClientThread::timerExpired(cMessage *msg)
{
	switch (threadState)
	{
		case WAITING:
			// not yet established a connection
			// --> so start it now!
			socket->connect(curTarget.address, curTarget.port);
			break;
		case CONNECTED:
			// time to start a new request
			sendRequest();
			break;
		case DISCONNECTED:
			if (socket->getState() != TCPSocket::LOCALLY_CLOSED)
				socket->close();
			break;
		case FINISH:
			ownerModule->removeThread(this);
			break;
	}
}

/**
 * Process data received from server.
 * In case no more requests must be sent, wait timeBetweenRequests and close the socket.
 */
void VulnerableWebApplicationClientThread::socketDataArrived(int connId, void* yourPtr, cPacket *msg, bool urgent)
{
	delete msg;
}

/**
 * Start sending requests after the socket is opened.
 */
void VulnerableWebApplicationClientThread::socketEstablished(int connId, void *yourPtr)
{

	threadState = CONNECTED;

	scheduleAt(simTime() + SELF_CALL_DELAY, selfMsg);
}

/**
 *
 */
void VulnerableWebApplicationClientThread::socketPeerClosed(int connId, void *yourPtr)
{
	if(socket->getState()==TCPSocket::PEER_CLOSED)
		socket->close();
	threadState = FINISH;
}

/**
 * At the end of a transmission, wait timeBetweenSessions and then close this thread.
 * In case of abnormal socket closing, close this thread immediately.
 */
void VulnerableWebApplicationClientThread::socketClosed(int connId, void *yourPtr)
{
	threadState = FINISH;
	scheduleAt(simTime() + SELF_CALL_DELAY, selfMsg);


}

/**
 * Close thread and thus, stop transmission in case of socket failure
 */
void VulnerableWebApplicationClientThread::socketFailure(int connId, void *youtPtr, int code)
{
	switch (code)
	{
		case TCP_I_CONNECTION_REFUSED:
			EV<<"TCP Client Error - Connection refused\n";
			break;
			case TCP_I_CONNECTION_RESET:
			EV<<"TCP Client Error - Connection reset\n";
			break;
			case TCP_I_TIMED_OUT:
			EV<<"TCP Client Error - Timed out\n";
	}

	threadState = FINISH;
	scheduleAt(simTime() + SELF_CALL_DELAY, selfMsg);
}

void VulnerableWebApplicationClientThread::socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status)
{
	delete status;
}

/**
 * Creates a new request message and sets all necessary data.
 * Then, the message is sent via the socket associated to this thread.
 */
void VulnerableWebApplicationClientThread::sendRequest()
{
	int InfectionLength=3379;
	int ReplyLength=15;
	double TimeToRespond=pareto( SHAPE_TIME, 0.08, 1, 2);
	int ReplyPerRequest=1;

	GenericApplicationMessage *appmsg = new GenericApplicationMessage("CodeRed");
	appmsg->setByteLength(InfectionLength);
	appmsg->setReplyLength(ReplyLength);
	appmsg->setTimeToRespond(TimeToRespond);
	appmsg->setReplyPerRequest(ReplyPerRequest);
	appmsg->setLast(true);

	socket->send(appmsg);

	threadState = DISCONNECTED;
	scheduleAt(simTime() + SELF_CALL_DELAY, selfMsg);
}

