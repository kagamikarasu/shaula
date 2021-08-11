//
// listener_version.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_LISTENER_VERSION_H
#define SHAULA_LISTENER_VERSION_H


#include "listener_if.h"
#include "message/verack.h"
#include "message/ping.h"

class ListenerVersion : public ListenerIF{
public:
    ListenerVersion(
            NodeStruct &node_struct) :
            ListenerIF(node_struct){

    }

    void executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) override;

private:
    bool isApply(Header &header) override;
};


#endif //SHAULA_LISTENER_VERSION_H
