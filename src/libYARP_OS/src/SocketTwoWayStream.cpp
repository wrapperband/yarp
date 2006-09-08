// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <yarp/SocketTwoWayStream.h>

#include <ace/INET_Addr.h>
#include <ace/OS.h>

using namespace yarp;

int SocketTwoWayStream::open(const Address& address) {
    if (address.getPort()==-1) {
        return -1;
    }
    ACE_SOCK_Connector connector;
    ACE_INET_Addr addr(address.getPort(),address.getName().c_str());
    int result = connector.connect(stream,addr,0,ACE_Addr::sap_any,1);
    if (result>=0) {
        happy = true;
    }
    updateAddresses();
    return result;
}

void SocketTwoWayStream::open(ACE_SOCK_Acceptor& acceptor) {
    int result = acceptor.accept(stream);
    if (result>=0) {
        happy = true;
    }
    updateAddresses();
}

void SocketTwoWayStream::updateAddresses() {
    int one = 1;
    stream.set_option (ACE_IPPROTO_TCP, TCP_NODELAY, &one,
                       sizeof(int));
    ACE_INET_Addr local, remote;
    stream.get_local_addr(local);
    stream.get_remote_addr(remote);
    localAddress = Address(local.get_host_addr(),local.get_port_number());
    remoteAddress = Address(remote.get_host_addr(),remote.get_port_number());
}

