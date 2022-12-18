#ifndef GENERICTCPAPPLICATIONCLIENTTHREAD_H_
#define GENERICTCPAPPLICATIONCLIENTTHREAD_H_

#include <omnetpp.h>
#include "VulnerableWebApplication.h"
#include "ReaSEDefs.h"

#define SELF_CALL_DELAY 0.0001
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
class REASE_API VulnerableWebApplicationClientThread : public VulnerableWebApplicationThreadBase
{
private:
	/// Communication partner of this thread
	TargetInfo curTarget;
	/// State of current thread
	int threadState;
	/// @}
	/// Self message for TCP state transitions
	cMessage *selfMsg;

public:
	VulnerableWebApplicationClientThread(TargetInfo &i);
	~VulnerableWebApplicationClientThread();
	void init(VulnerableWebApplication *owner, TCPSocket *sock);
	void timerExpired(cMessage *msg);

protected:
	// Interface Methods
	void socketDataArrived(int connId, void *youtPtr, cPacket *msg, bool urgent);
	void socketEstablished(int connId, void *youtPtr);
	void socketPeerClosed(int connId, void *youtPtr);
	void socketClosed(int connId, void *youtPtr);
	void socketFailure(int connId, void *youtPtr, int code);
	void socketStatusArrived(int connId, void *youtPtr, TCPStatusInfo *status);

	/// @brief Create a request message and send it to the server
	void sendRequest();
};

#endif

