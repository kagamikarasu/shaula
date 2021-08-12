//
// listener_verack.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_LISTENER_VERACK_H
#define SHAULA_LISTENER_VERACK_H

#include "listener_if.h"

class ListenerVerack : public ListenerIF {
public:
    explicit ListenerVerack(
            NodeStruct &node_struct) :
            ListenerIF(node_struct){
    }

    void executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) override;

};

#endif //SHAULA_LISTENER_VERACK_H
