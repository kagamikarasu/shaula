//
// listener_version.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include "listener_version.h"

void ListenerVersion::executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) {
    if(!isApply(header)){
        return;
    }

    timeout_.cancel();
    last_recv_.setVersion(body);

    if(last_send_.hasHeader() && last_send_.getHeader().getCommand() == CommandDef.VERSION){
        return;
    }

    Version::send(socket_, yield, last_send_, endpoint_);
    Verack::send(socket_, yield, last_send_);
    Ping::send(socket_, yield, last_send_);
}

bool ListenerVersion::isApply(Header &header) {
    if(header.getCommand() == CommandDef.VERSION){
        return true;
    }
    return false;
}
