//
// Session.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_SESSION_H
#define SHAULA_SESSION_H


#include "Node.h"

class Session : public Node{
        boost::asio::ip::tcp::acceptor &acceptor_;
public:

    explicit Session(boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &acceptor);

    void receive(const boost::asio::yield_context &yield);

    void accept(const boost::asio::yield_context &yield);

    void run();

    void close();
};


#endif //SHAULA_SESSION_H
