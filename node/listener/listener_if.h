//
// listener_if.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_LISTENER_IF_H
#define SHAULA_LISTENER_IF_H

#include <message/last/last_send.h>
#include <message/last/last_recv.h>
#include "node/node_struct.h"

class ListenerIF{
protected:
    /**
     * io_context address
     */
    boost::asio::io_context& io_context_;

    /**
     * socket address
     */
    boost::asio::ip::tcp::socket& socket_;

    /**
     * deadline_timer address
     */
    boost::asio::deadline_timer& timeout_;

    /**
     * Endpoint
     */
    Endpoint& endpoint_;

    /**
     * LastSend Data
     */
    LastSend& last_send_;

    /**
     * LastReceive Data
     */
    LastRecv& last_recv_;
public:
    /**
     *
     * @param node_struct_
     */
    explicit ListenerIF(
            NodeStruct &node_struct_) :
            io_context_(node_struct_.io_context_),
            socket_(node_struct_.socket_),
            timeout_(node_struct_.timeout_),
            endpoint_(node_struct_.endpoint_),
            last_send_(node_struct_.last_send_),
            last_recv_(node_struct_.last_recv_){
    }

    /**
     * Listener executor
     * @param header
     * @param body
     * @param yield
     */
    virtual void executor(
            Header &header,
            std::vector<unsigned char> &body,
            const boost::asio::yield_context &yield
            ) = 0;
private:
    virtual bool isApply(Header &header) = 0;
};

#endif //SHAULA_LISTENER_IF_H
