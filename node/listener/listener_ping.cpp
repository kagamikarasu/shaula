//
// listener_ping.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include <message/ping.h>
#include <message/pong.h>
#include "listener_ping.h"

void ListenerPing::executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) {
    if(header.getCommand() != CommandDef.PING){
        return;
    }

    Pong::send(socket_, yield, last_send_, std::make_unique<Ping>(body)->getNonce());
}
