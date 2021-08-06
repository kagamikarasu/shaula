//
// listener_ping.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_LISTENER_PING_H
#define SHAULA_LISTENER_PING_H


#include "listener_if.h"

class ListenerPing : public ListenerIF {
public:
    ListenerPing(
            NodeStruct &node_struct,
            LastRecv &last_recv) :
            ListenerIF(node_struct,
                       last_recv
                       ){

    }

    void executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) override;

private:
    bool isApply(Header &header) override;
};


#endif //SHAULA_LISTENER_PING_H
