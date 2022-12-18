package rease.nodes.inet;

import inet.base.NotificationBoard;
import inet.linklayer.ethernet.EthernetInterface;
import inet.linklayer.ppp.PPPInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.nodes.inet.NetworkLayer;
import inet.util.NAMTraceWriter;
import rease.applications.pingApp.GenericICMPPingApplication;
import rease.applications.tcpApp.GenericTCPApplication;
import rease.transport.tcp.TCP_hack;
import rease.transport.udp.UDP_hack;
import inet.util.TCPDump;

//
// BackupServer: Server system for backup traffic profile using TCP as 
// transport protocol.
// This profile generates many large client requests and only few
// server replies.
//
// \IP host with TCP, UDP layers and applications.
//
module HTTPSServer
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
                isServer = true;
                profileNumber = 2;
                port = 443;
                @display("p=163,67;i=block/app");
        }
        tcpApp2: GenericTCPApplication {
            parameters:
                isServer = true;
                profileNumber = 1;
                port = 22;
                @display("p=240,67;i=block/app");

        }
        tcp: TCP_hack {
            parameters:
                maxThreadCount = maxTCPThreadCount;
                @display("p=163,154;i=block/wheelbarrow");
        }
        udp: UDP_hack {
            parameters:
                @display("p=272,154;i=block/transport");
        }
        pingApp: GenericICMPPingApplication {
            parameters:
                isServer = true;
                profileNumber = 21;
                port = 0;
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
                @display("p=209,393,row,90;q=txQueue;i=block/ifcard");
        }
        eth[sizeof(ethg)]: EthernetInterface {
            parameters:
                @display("p=287,393,row,90;q=txQueue;i=block/ifcard");
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

        tcp.ipOut --> networkLayer.tcpIn;
        tcp.ipIn <-- networkLayer.tcpOut;

        udp.ipOut --> networkLayer.udpIn;
        udp.ipIn <-- networkLayer.udpOut;

        networkLayer.pingOut --> pingApp.pingIn;
        networkLayer.pingIn <-- pingApp.pingOut;

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
