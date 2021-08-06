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

class ListenerVersion : public ListenerIF{
public:
    ListenerVersion(
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


#endif //SHAULA_LISTENER_VERSION_H