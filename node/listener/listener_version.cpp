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
}

bool ListenerVersion::isApply(Header &header) {
    if(header.getCommand() == CommandDef.VERSION){
        return true;
    }
    return false;
}
