package rease.nodes.inet;

import inet.base.NotificationBoard;
import inet.linklayer.ethernet.EthernetInterface;
import inet.linklayer.ppp.PPPInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.nodes.inet.NetworkLayer;
import inet.util.NAMTraceWriter;
import rease.transport.tcp.TCP_hack;
import rease.applications.generic.InetUser;
import rease.applications.pingApp.GenericICMPPingApplication;
import rease.applications.tcpApp.GenericTCPApplication;
import rease.applications.udpApp.GenericUDPApplication;
import rease.transport.udp.UDP_hack;
import rease.applications.TCPWorm.VulnerableWebApplication;
import inet.util.TCPDump;
//
// Default IP host which replaces the standard host of the original
// INET framework.
// This host system consists of TCP, UDP layers and applications.
// In comparison to StandardHost TCP_hack and UDP_hack are used.
// In addition the GenericXXApplications are used for traffic generation
// instead of the original XXApp implementations.
// Thus, only a single application is necessary per protocol type.
//
// Finally, the simple module InetUser is contained that actually requests
// traffic profiles at random times and therefore, creates self-similar
// background traffic.
//
module HTTPServer
{
    parameters:
        @node();
        int namid;
        int maxTCPThreadCount;
    gates:
        inout pppg[];
        inout ethg[];
    submodules:
        namTrace: NAMTraceWriter {
            parameters:
                namid = namid;
                @display("p=60,310;i=block/sink");

        }
        inetUser: InetUser {
            parameters:
                @display("p=60,390;i=abstract/person");
                webServer=true;

        }
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=60,70;i=block/control");

        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=60,150;i=block/table");

        }
        routingTable: RoutingTable {
            parameters:
                IPForward = false;
                routerId = "";
                routingFile = "";
                @display("p=60,230;i=block/table");

        }
        tcpApp1: GenericTCPApplication {
            parameters:
                isServer = false;
                profileNumber = -2;
                port = 0;
                noThreads = 0;
                @display("p=147,43;i=block/app");

        }
        tcpApp2: GenericTCPApplication {
            parameters:
                isServer = true;
                profileNumber = 3;
                port = 80;
                @display("p=311,49;i=block/app");

        }
        VulnerableWebApplication: VulnerableWebApplication {
            parameters:
                @display("p=233,43;i=old/telnet");
        }
        tcp: TCP_hack {
            parameters:
                maxThreadCount = maxTCPThreadCount;
                @display("p=163,154;i=block/wheelbarrow");

        }
        udpApp: GenericUDPApplication {
            parameters:
                isServer = false;
                profileNumber = 13;
                port = 500;
                noThreads = 0;
                @display("i=block/app;p=376,109");

        }
        udp: UDP_hack {
            parameters:
                @display("p=272,154;i=block/transport");

        }
        pingApp: GenericICMPPingApplication {
            parameters:
                isServer = false;
                profileNumber = 21;
                port = 0;
                noThreads = 0;
                @display("i=block/app;p=343,200");

        }
        networkLayer: NetworkLayer {
            parameters:
                proxyARP = false;
                @display("p=248,247;i=block/fork;q=queue");

            gates:
                ifIn[sizeof(pppg)+sizeof(ethg)];
                ifOut[sizeof(pppg)+sizeof(ethg)];
        }
        ppp[sizeof(pppg)]: PPPInterface {
            parameters:
                @display("p=186,406,row,90;q=txQueue;i=block/ifcard");

        }
        eth[sizeof(ethg)]: EthernetInterface {
            parameters:
                @display("p=311,418,row,90;q=txQueue;i=block/ifcard");

        }
        tcpdump: TCPDump {
            parameters:
                @display("p=240,330;i=abstract/cache_s");
            gates:
                ifIn[sizeof(pppg)+sizeof(ethg)];
                in2[sizeof(pppg)+sizeof(ethg)];
                ifOut[sizeof(pppg)+sizeof(ethg)];
                out2[sizeof(pppg)+sizeof(ethg)];
        }
    connections allowunconnected:
        tcpApp1.tcpOut --> tcp.appIn++;
        tcpApp1.tcpIn <-- tcp.appOut++;

        tcpApp2.tcpOut --> tcp.appIn++;
        tcpApp2.tcpIn <-- tcp.appOut++;

        VulnerableWebApplication.tcpOut --> tcp.appIn++;
        VulnerableWebApplication.tcpIn <-- tcp.appOut++;

        tcp.ipOut --> networkLayer.tcpIn;
        tcp.ipIn <-- networkLayer.tcpOut;

        udpApp.udpOut --> udp.appIn++;
        udpApp.udpIn <-- udp.appOut++;

        udp.ipOut --> networkLayer.udpIn;
        udp.ipIn <-- networkLayer.udpOut;

        networkLayer.pingOut --> pingApp.pingIn;
        networkLayer.pingIn <-- pingApp.pingOut;

        VulnerableWebApplication.stateIn <-- tcpApp2.stateOut;
        // connections to network outside
        for i=0..sizeof(pppg)-1 {
            pppg[i] <--> ppp[i].phys;
            ppp[i].netwOut --> tcpdump.ifIn[i]; //I.R.
            tcpdump.out2[i] --> networkLayer.ifIn[i];
            ppp[i].netwIn <-- tcpdump.ifOut[i];
            tcpdump.in2[i] <-- networkLayer.ifOut[i];
        }

        for i=0..sizeof(ethg)-1 {
            ethg[i] <--> eth[i].phys;
            eth[i].netwOut --> tcpdump.ifIn[sizeof(pppg)+i]; //I.R.
            tcpdump.out2[sizeof(pppg)+i] --> networkLayer.ifIn[sizeof(pppg)+i];
            eth[i].netwIn <-- tcpdump.ifOut[sizeof(pppg)+i];
            tcpdump.in2[sizeof(pppg)+i] <-- networkLayer.ifOut[sizeof(pppg)+i];
        }

}

