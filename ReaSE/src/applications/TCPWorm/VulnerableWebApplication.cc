#include "VulnerableWebApplication.h"
#include "VulnerableWebApplicationClientThread.h"
#include "IPControlInfo_hacked_m.h"
#include "IPv6ControlInfo_hacked_m.h"
#include "TGMNetworkConfigurator.h"
#include <iostream>
#include <fstream>
#include <string.h>

using std::cerr;
using std::cout;
using std::endl;
using std::fstream;
using namespace std;
using std::cerr;
using std::cout;
using std::endl;

const int IP_NET_SHIFT = 16;
/**
 * @brief Implementation of a TCP application.
 *
 * TCP servers open a welcome socket and react on incoming connections.
 * New connections of TCP clients can be triggered by the connection
 * manager.
 * Overload situations at servers are simulated by limiting the number
 * of TCP connections that may open at the same time.
 *
 * @class VulnerableWebApplication
 */
Define_Module(VulnerableWebApplication);
VulnerableWebApplication::VulnerableWebApplication()
{
	// we have to set an appropriate application type
	// to register at the InetUser

	CurrentthreadCount = 0;


}

VulnerableWebApplication::~VulnerableWebApplication()
{
	ThreadList::iterator it = threadList.begin();
	while (it != threadList.end())
	{
		delete (*it)->getSocket();
		delete (*it);
		it++;
	}
	if (probingTimer)
	{
		if (probingTimer->isScheduled())
			cancelAndDelete(probingTimer);
		else
			delete probingTimer;
	}
}
void VulnerableWebApplication::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage())
	{
		if (strcmp("timeoutForProbingPacket", msg->getName())==0 && state==1)
		{
			ev << "timeoutForProbingPacket at time " <<  simTime() <<"for "<< getFullPath()  <<endl;
			sendProbingPacket();
		}
		if (strcmp("threadtimer", msg->getName())==0)
		{
			EV << "we are in if (strcmp(threadtimer, msg->getName())==0)\n";
			VulnerableWebApplicationThreadBase *thread = (VulnerableWebApplicationThreadBase *) msg->getContextPointer();
			thread->timerExpired(msg);
		}
		// time to write state to file
		if (strcmp("timeoutForStateTimer", msg->getName())==0)
		{
			// file that save the state of node
			if (state==1)
			{
				if( RecoveryProbability>uniform(0, 1, 0))
				{
					state=2;
					EV<< "at time " << simTime() << " " << getFullPath() << " is recovered \n";
					ThreadList::iterator it = threadList.begin();
					while (it != threadList.end())
					{
						delete (*it)->getSocket();
						delete (*it);
						it++;
					}
					if (probingTimer)
					{
						if (probingTimer->isScheduled())
							cancelAndDelete(probingTimer);
						else
							delete probingTimer;
					}
				}
			}
			// file that save the state of node
			std::ofstream state_file;
			char filename[100];
			strcpy(filename, "D:\\");
			strcat(filename, getFullPath().c_str());
			strcat(filename, ".txt");
			state_file.open (filename, std::ofstream::out | std::ofstream::app);
			state_file << state <<" ";
			state_file.close();
			ev << "the state of " << getFullPath() << " at time "<< simTime() <<" is "<< state <<endl;
			scheduleAt(simTime() + StateTimeUnit, StateTimer);
		}

	}
	else if ((msg->getName()[0]=='C')&&(msg->getName()[1]=='o')&&(msg->getName()[2]=='d')&&(msg->getName()[3]=='e') )
	{
		if(!state)
		{
			state=1;
			// now i'm an active worm and start probing
			ev << msg->getName()<<endl;
			//file that save infection path
			std::ofstream infection_path_file;
			infection_path_file.open ("D:\\infection_path_file.txt", std::ofstream::out | std::ofstream::app);
			infection_path_file << msg->getName()<<endl;
			infection_path_file.close();
			scheduleAt(simTime() , probingTimer);
		}
	}
	else
	{
		if (state!=2)
				{
					TCPSocket *socket = socketMap.findSocketFor(msg);
					if(socket)
						socket->processMessage(msg);
				}
	}

}
void VulnerableWebApplication::sendProbingPacket()
{
	EV << " sendProbingPacket Called " <<endl;
	EV << " CurrentthreadCount " << CurrentthreadCount << endl;
	while(CurrentthreadCount<AllThreadCount)
	{
		EV << " while(CurrentthreadCount<AllThreadCount) " <<endl;
		IPvXAddress targetAddr;

		unsigned int tmpSubnetAddr;
		IPvXAddress SubnetAddr;
		IInterfaceTable* ift = IPAddressResolver().findInterfaceTableOf(getParentModule());
		if (ift->getInterface(1)->ipv4Data() != NULL) {
			tmpSubnetAddr = ift->getInterface(1)->ipv4Data()->getIPAddress().getInt();
			tmpSubnetAddr = tmpSubnetAddr >> IP_NET_SHIFT;
			tmpSubnetAddr = tmpSubnetAddr << IP_NET_SHIFT;
		}
		SubnetAddr.set(tmpSubnetAddr);

		unsigned int tmpStartAddr;
		IPvXAddress StartAddr;
		tmpStartAddr = addrStart.get4().getInt() << IP_NET_SHIFT;
		tmpStartAddr = tmpStartAddr >> IP_NET_SHIFT;
		tmpStartAddr=tmpSubnetAddr+tmpStartAddr;
		StartAddr.set(tmpStartAddr);
		EV << " StartAddr " << StartAddr << endl;

		unsigned int tmpEndAddr;
		IPvXAddress EndAddr;
		tmpEndAddr = addrEnd.get4().getInt() << IP_NET_SHIFT;
		tmpEndAddr = tmpEndAddr >> IP_NET_SHIFT;
		tmpEndAddr=tmpSubnetAddr+tmpEndAddr;
		EndAddr.set(tmpEndAddr);
		EV << " EndAddr " << EndAddr << endl;

		IPvXAddress subnet1_addr;
		IPvXAddress subnet1_start_addr;
		IPvXAddress subnet1_end_addr;

		IPvXAddress subnet2_addr;
		IPvXAddress subnet2_start_addr;
		IPvXAddress subnet2_end_addr;

		IPvXAddress subnet3_addr;
		IPvXAddress subnet3_start_addr;
		IPvXAddress subnet3_end_addr;

		IPvXAddress subnet4_addr;
		IPvXAddress subnet4_start_addr;
		IPvXAddress subnet4_end_addr;

		const char *subnet1 = "0.1.0.0";
		const char *subnet1_start = "0.1.0.8";
		const char *subnet1_end = "0.1.0.57";

		const char *subnet2 = "0.2.0.0";
		const char *subnet2_start = "0.2.0.8";
		const char *subnet2_end = "0.2.0.57";

		const char *subnet3 = "1.2.0.0";
		const char *subnet3_start = "1.2.0.8";
		const char *subnet3_end = "1.2.0.57";

		const char *subnet4 = "1.3.0.0";
		const char *subnet4_start = "1.3.0.8";
		const char *subnet4_end = "1.3.0.57";

		subnet1_addr.set(subnet1);
		subnet1_start_addr.set(subnet1_start);
		subnet1_end_addr.set(subnet1_end);

		subnet2_addr.set(subnet2);
		subnet2_start_addr.set(subnet2_start);
		subnet2_end_addr.set(subnet2_end);

		subnet3_addr.set(subnet3);
		subnet3_start_addr.set(subnet3_start);
		subnet3_end_addr.set(subnet3_end);

		subnet4_addr.set(subnet4);
		subnet4_start_addr.set(subnet4_start);
		subnet4_end_addr.set(subnet4_end);

		EV << "subnet1_addr"<< subnet1_addr << endl;
		EV << "subnet2_addr"<< subnet2_addr << endl;
		EV << "	subnet3_addr"<< subnet3_addr << endl;
		EV << "subnet4_addr"<< subnet4_addr << endl;

		unsigned int tmpSubnetAddr_ClassA;
		IPvXAddress SubnetAddr_ClassA;
		tmpSubnetAddr_ClassA = tmpSubnetAddr >> 24;
		tmpSubnetAddr_ClassA = tmpSubnetAddr << 24;
		SubnetAddr_ClassA.set(tmpSubnetAddr_ClassA);
		EV << " SubnetAddr_ClassA " << SubnetAddr_ClassA <<endl;

		IPvXAddress subnet1_ClassA;
		IPvXAddress subnet2_ClassA;

		const char *tmpsubnet1_ClassA = "0.0.0.0";
		const char *tmpsubnet2_ClassA = "1.0.0.0";

		subnet1_ClassA.set(tmpsubnet1_ClassA);
		subnet2_ClassA.set(tmpsubnet2_ClassA);

		EV << " subnet1_ClassA " << subnet1_ClassA <<endl;
		EV << " subnet2_ClassA " << subnet2_ClassA <<endl;

		double random1=uniform(0, 1, 4);
		EV << " random1 " << random1 <<endl;

		if (0.125 >=random1 )// the ip address choose randomly
		{
			EV << " if (0.125 >=random1 ) " <<endl;
			double random=uniform(0, 1, 4);
			if(random<=0.25)
			{
				targetAddr.set(intuniform(subnet1_start_addr.get4().getInt(), subnet1_end_addr.get4().getInt(), 4));
			}
			else if(0.25<random && random<=0.5)
			{
				targetAddr.set(intuniform(subnet2_start_addr.get4().getInt(), subnet2_end_addr.get4().getInt(), 4));
			}
			else if(0.5<random && random<=0.75)
			{
				targetAddr.set(intuniform(subnet3_start_addr.get4().getInt(), subnet3_end_addr.get4().getInt(), 4));
			}
			else if(0.75<random && random<=1)
			{
				targetAddr.set(intuniform(subnet4_start_addr.get4().getInt(), subnet4_end_addr.get4().getInt(), 4));
			}
		}
		else if (0.125 < random1 && random1<=0.625)// the ip address choose in same Class A
		{
			EV << " else if (0.125 < random1 && random1<=0.625) " <<endl;
			if(SubnetAddr_ClassA.equals(subnet1_ClassA))
			{
				EV << " if(SubnetAddr_ClassA.equals(subnet1_ClassA)) " <<endl;
				double random=uniform(0, 1, 4);
				if(random<=0.5)
				{
					targetAddr.set(intuniform(subnet1_start_addr.get4().getInt(), subnet1_end_addr.get4().getInt(), 4));
				}
				else if(0.5<random && random<=1.0)
				{
					targetAddr.set(intuniform(subnet2_start_addr.get4().getInt(), subnet2_end_addr.get4().getInt(), 4));
				}
			}
			else if(SubnetAddr_ClassA.equals(subnet2_ClassA))
			{
				EV << " else if(SubnetAddr_ClassA.equals(subnet2_ClassA)) " <<endl;
				double random=uniform(0, 1, 4);
				if(random<=0.5)
				{
					targetAddr.set(intuniform(subnet3_start_addr.get4().getInt(), subnet3_end_addr.get4().getInt(), 4));
				}
				else if(0.5<random && random<=1.0)
				{
					targetAddr.set(intuniform(subnet4_start_addr.get4().getInt(), subnet4_end_addr.get4().getInt(), 4));
				}
			}

		}
		else if(0.625 < random1 && random1<=1)// the ip address choose in same Class B
		{
			EV << " else if(0.625 < random1 && random1<=1) " <<endl;
			targetAddr.set(intuniform(tmpStartAddr, tmpEndAddr, 4));
		}
		//const char *tmp = "1.3.0.45";
		//targetAddr.set(tmp);
		ev << "target address is "  << targetAddr << endl;

		TCPSocket *socket = new TCPSocket();
		sourcePort = intuniform(1500,60000);
		socket->bind(IPvXAddress(), sourcePort);
		socket->setOutputGate(gate("tcpOut"));

		TargetInfo curTargetInfo;
		curTargetInfo.port=victimPort;
		curTargetInfo.address=targetAddr;

		VulnerableWebApplicationThreadBase *t = new VulnerableWebApplicationClientThread(curTargetInfo);
		socket->setCallbackObject(t);
		t->init(this, socket);
		socketMap.addSocket(socket);
		CurrentthreadCount++;
		threadList.push_back(t);
	}

}
/**
 * Closes the given thread and its associated socket.
 * This method is called whenever a TCP communication has finished.
 *
 * @param thread Thread that should be closed
 */
void VulnerableWebApplication::removeThread(VulnerableWebApplicationThreadBase *thread)
{
	ThreadList::iterator it = threadList.begin();
	while (it != threadList.end())
		if (thread == *it)
			break;
		else
			it++;
	if (it != threadList.end())
		threadList.erase(it);
	else
		opp_error("cannot find TCP thread in threadList\n");

	delete socketMap.removeSocket(thread->getSocket());
	delete thread;
	CurrentthreadCount--;
	///// replace a new thread instead of closed thread if web server is infected
	EV << " removeThread Called " <<endl;
	if(state==1)
		sendProbingPacket();
}

/**
 * Closes the given thread and its associated socket and sends statistics to
 * InetUser.
 *
 * @param thread Thread that should be closed
 * @param stat Statistics collected about the previous transmission
 */
void VulnerableWebApplication::removeThread(VulnerableWebApplicationThreadBase *thread, TransmissionStatistics stat)
{
	removeThread(thread);
}

/**
 * Call initialize method of super class that registers at
 * InetUser and ConnectionManager. Then open a welcome socket
 * in case of a server instance.
 */
void VulnerableWebApplication::initialize(int stages)
{
	RecoveryProbability = par("RecoveryProbability");
	StateTimeUnit= par("StateTimeUnit");
	sourcePort = intuniform(1500,60000);
	victimPort = par("listenAndVictimPort");
	AllThreadCount = par("ThreadCount");
	infectionLength = par("infectionLength");
	StateTimer = new cMessage("timeoutForStateTimer");
	probingTimer = new cMessage("timeoutForProbingPacket");

	const char *beginString = par("addressRangeStart");
	addrStart.set(beginString);
	const char *endString = par("addressRangeEnd");
	addrEnd.set(endString);

	startTime = par("startProbing");
	startTimeDiff = par("startProbingDiff");
	// a web server is infected at start of propagation
	if ( (getFullPath())[14]=='_'&& (getFullPath())[15]=='H'&& (getFullPath())[16]=='T'&& (getFullPath())[17]=='T'&& (getFullPath())[18]=='P'&& (getFullPath())[19]=='S'&& (getFullPath())[20]=='e'&& (getFullPath())[21]=='r'&& (getFullPath())[22]=='v'&& (getFullPath())[23]=='e'&& (getFullPath())[24]=='r'&& (getFullPath())[25]=='1'&& (getFullPath())[26]=='2'&& (getFullPath())[27]=='_'&& (getFullPath())[28]=='T'&& (getFullPath())[29]=='A'&& (getFullPath())[30]=='S'&& (getFullPath())[31]=='0')
	{
		state = 1;
		// file that save the state of node
		std::ofstream state_file;
		char filename[100];
		strcpy(filename, "D:\\");
		strcat(filename, getFullPath().c_str());
		strcat(filename, ".txt");
		state_file.open (filename, std::ofstream::out | std::ofstream::app);
		state_file << state <<" ";
		state_file.close();

		ev << "at the beginning, " << getFullPath() << " is infected" << endl;

		scheduleAt(simTime() + startTime + startTimeDiff, probingTimer);
	}
	else
	{
		state = 0;
		// file that save the state of node
		std::ofstream state_file;
		char filename[100];
		strcpy(filename, "D:\\");
		strcat(filename, getFullPath().c_str());
		strcat(filename, ".txt");
		state_file.open (filename, std::ofstream::out | std::ofstream::app);
		state_file << state <<" ";
		state_file.close();
		ev << "at the beginning, Worm at " << getFullPath() << " is susceptible" << endl;
	}

	scheduleAt(simTime() + StateTimeUnit, StateTimer);

}
void VulnerableWebApplication::finish()
{

	//TODO:
}
