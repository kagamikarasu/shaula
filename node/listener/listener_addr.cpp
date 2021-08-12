//
// listener_addr.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "listener_addr.h"
#include <client/client_pool.h>

void ListenerAddr::executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) {
    if(!isApply(header)){
        return;
    }

    ClientPool::add(io_context_, std::make_unique<Addr>(body)->getAddrList());
    ClientPool::resize(io_context_);
}

bool ListenerAddr::isApply(Header &header) {
    if(header.getCommand() == CommandDef.ADDR){
        return true;
    }
    return false;
}
