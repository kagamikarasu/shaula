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

#include "node/node.h"

/**
 * Session Class
 * Manage a single connection
 * Basically the same as the Client Class.
 */
class Session : public Node{
private:
    /**
     * Acceptor
     */
    boost::asio::ip::tcp::acceptor &acceptor_;
public:
    /**
     * Flag to re-instate the standby state when disconnected.
     * Default : True
     * Use False when testing.
     */
     bool is_session_re_run_ = true;
public:
    /**
     *
     * @param ioContext
     * @param acceptor
     */
    explicit Session(boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &acceptor);

    /**
     * Start a new coroutine and make a connection.
     * It sends and receives data asynchronously.
     */
    void run();

    /**
     * Close the current connection and accept a new one.
     */
    void close() override;

    /**
     * Return Remote Address
     */
    std::string getAddress();

private:
    /**
     * Async_accept and Receive
     * @param yield
     */
    void accept(const boost::asio::yield_context &yield);

    /**
     * Async_receive
     * @param yield
     */
    void receive(const boost::asio::yield_context &yield);

};


#endif //SHAULA_SESSION_H
