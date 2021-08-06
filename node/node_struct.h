//
// node_struct.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_NODE_STRUCT_H
#define SHAULA_NODE_STRUCT_H

#include <boost/asio/deadline_timer.hpp>

struct NodeStruct {
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket& socket_;
    boost::asio::deadline_timer& timeout_;
};

#endif //SHAULA_NODE_STRUCT_H
