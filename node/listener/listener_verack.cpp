//
// listener_verack.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include <message/verack.h>
#include <message/get_addr.h>
#include "listener_verack.h"

void
ListenerVerack::executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) {
    if(header.getCommand() != CommandDef.VERACK){
        return;
    }

    if(!last_send_.isEnableVerack()){
        return;
    }

    Verack::send(socket_, yield, last_send_);
    GetAddr::send(socket_, yield, last_send_);
}

