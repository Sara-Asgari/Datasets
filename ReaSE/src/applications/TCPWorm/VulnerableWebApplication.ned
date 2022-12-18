package rease.applications.TCPWorm;


//
// This simple module implements a generator for a worm propagation.
// The infected hosts start sending probing packets to random addresses
// of the given address range. If another UDPWormVictim, that is not yet
// infected, receives such a probing packet it switches its state to 
// infected and starts itself sending probing packets. Having sent a
// maximum number of probing packets, the host switch to inactive.
//
simple VulnerableWebApplication

{
    parameters:
        double StateTimeUnit @unit(s);
        int listenAndVictimPort;
        string addressRangeStart;
        string addressRangeEnd;
        double startProbing @unit(s);
        double startProbingDiff @unit(s);
        double RecoveryProbability;//probability that in each time unit the host is recovered
        int infectionLength @unit(B);
		int ThreadCount;
    gates:
        input tcpIn;
        output tcpOut;
        input stateIn;

}
