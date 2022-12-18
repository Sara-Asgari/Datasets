#ifndef VULNERABLEWEBAPPLICATION_H_
#define VULNERABLEWEBAPPLICATION_H_

#include <omnetpp.h>
#include <list>
#include <limits.h>
#include "GenericApplication.h"
#include "TCPSocket.h"
#include "TCPSocketMap.h"
#include <omnetpp.h>
#include "IPvXAddress.h"
#include "ReaSEDefs.h"
#include "TCPSocket.h"
#include "TCPSocketMap.h"
#include <string>
#include <map>
#include <crng.h>
#include <cstringtokenizer.h>
#include <iostream>
#include <ostream>
#include "ModuleAccess.h"
#include "ConnectionManager.h"

const int FIRST_ATTACK_ID_OF_WORM_SPREAD = 10000;
class VulnerableWebApplicationThreadBase;

/**
 * @brief Implementation of a TCP application.
 *
 * TCP servers open a welcome socket and react on incoming connections.
 * New connections of TCP clients can be triggered by the connection
 * manager.
 * Overload situations at servers are simulated by limiting the number
 * of TCP connections that may open at the same time.
 *
 * @class GenericTCPApplication
 */
class REASE_API VulnerableWebApplication:public cSimpleModule
{
	typedef std::list<VulnerableWebApplicationThreadBase*> ThreadList;
protected:
	/// Fixed time unit that state of node is written to file and recovey is done on that times also
	double StateTimeUnit;
	/// IP address range used for probing packets
	/// @{
	IPvXAddress addrStart, addrEnd;
	/// @}
	/// Source port of probing packets
	int sourcePort;
	/// Destination port of probing packets
	int victimPort;
	/// Timer message indicating that a probing packet should be sent
	cMessage *probingTimer;
	/// Timer message indicating that state should be written to file
	cMessage *StateTimer;
	/// Start time of worm propagation
	double startTime;
	double startTimeDiff;
	/// Indicates if the host is already infected or vulnerable or recovered
	// 0:susceptible, 1:infected, 2:recovered
	int state;
	/// Length of probing
	int infectionLength;
	//probability that in each time unit the host is recovered
	double RecoveryProbability;
	/// Map that contains sockets of all associated threads
	TCPSocketMap socketMap;
	/// List of all associated threads
	ThreadList threadList;
	/// Number of threads that are open currently
	int CurrentthreadCount;
	/// number of threads that should  be open at the same time
	int AllThreadCount;

public:
	VulnerableWebApplication();
   ~VulnerableWebApplication();
	/// @brief Closes thread and associated socket
	void removeThread(VulnerableWebApplicationThreadBase *thread);
	/// @brief Closes thread and associated socket and sends statistics to InetUser
	void removeThread(VulnerableWebApplicationThreadBase *thread, TransmissionStatistics s);
	/// @brief Starts a new connection to a server (client only!)
	void handleMessage(cMessage *msg);
    void sendProbingPacket();
protected:
	/// @brief Register at InetUser and ConnectionManager and open welcome socket (server only!)
    void initialize(int stages);
	void finish();

};

/**
 * @brief Abstract class for implementation of client and server threads.
 *
 * These threads resemble the actual client and server functionality and
 * implement the communciation endpoints in case of a TCP transmission.
 *
 * @class VulnerableWebApplicationThreadBase
 */
class REASE_API VulnerableWebApplicationThreadBase : public cPolymorphic, public TCPSocket::CallbackInterface
{
protected:
	/// Pointer to application that started this thread
	VulnerableWebApplication *ownerModule;
	/// Socket used by this thread
	TCPSocket *socket;


protected:
	/// Interface Methods of TCPSocket
	/// @{
	/// @brief Called in case packets arrived at the socket
	virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent) = 0;
	/// @brief Called in case socket is opened
	virtual void socketEstablished(int connId, void *yourPrt) = 0;
	/// @brief Called in case the peering socket is closed
	virtual void socketPeerClosed(int connId, void *yourPtr) = 0;
	/// @brief Called in case the socket is closed
	virtual void socketClosed(int connId, void *yourPtr) = 0;
	/// @brief Close thread in case of socket failure
	virtual void socketFailure(int connId, void *yourPtr, int code) {ownerModule->removeThread(this); };
	/// @brief
	virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {delete status; };
	/// @}

public:
	VulnerableWebApplicationThreadBase() {socket = NULL; ownerModule = NULL; };
	virtual ~VulnerableWebApplicationThreadBase() {};
	/// Set owner application module and socket of this thread
	virtual void init(VulnerableWebApplication *owner, TCPSocket *sock) {ownerModule = owner; socket = sock; };
	/// Handling of internal timer messages
	virtual void timerExpired(cMessage *msg) = 0;
	/// Return instance of TCPApplication that started the thread
	VulnerableWebApplication *getOwnerModule() {return ownerModule; };
	/// Return socket used for this thread
	TCPSocket *getSocket() {return socket; };
	void scheduleAt(simtime_t t, cMessage *msg) {msg->setContextPointer(this); ownerModule->scheduleAt(t, msg); };
	/// Delegate message canceling to owner module
	void cancelEvent(cMessage *msg) {ownerModule->cancelEvent(msg); };
	/// Delegate message canceling and deletion to owner module
	void cancelAndDelete(cMessage *msg) {ownerModule->cancelAndDelete(msg); };
};

#endif /*VULNERABLEWEBAPPLICATION_H_*/
