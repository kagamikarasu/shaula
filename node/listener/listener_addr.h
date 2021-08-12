//
// listener_addr.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_LISTENER_ADDR_H
#define SHAULA_LISTENER_ADDR_H

#include "listener_if.h"
#include "message/addr.h"

class ListenerAddr : public ListenerIF{
public:
    explicit ListenerAddr(
            NodeStruct &node_struct) :
            ListenerIF(node_struct){
    }

    void executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) override;

};

#endif //SHAULA_LISTENER_ADDR_H
