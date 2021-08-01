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

#include <boost/thread.hpp>
#include "node/node.h"

/**
 * Session Class
 * Manage a single connection
 * Basically the same as the Client Class.
 */
class Session : public Node{
    /**
     * Run Thread ID
     */
    std::string run_thread_id_;

    /**
     * Acceptor
     */
    boost::asio::ip::tcp::acceptor &acceptor_;

    /**
     * Last received version message
     */
    std::shared_ptr<Version> version_;
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
     * Return Version Message
     * @return
     */
    std::shared_ptr<Version> getVersion();

    /**
     * Close the current connection and accept a new one.
     */
    void close();

    /**
     * Check Connection
     * @return
     */
    bool isOpen();

    /**
     * Return Remote Address
     */
    std::string getAddress();

    /**
     * Return ThreadId
     * @return
     */
    std::string getRunThreadId();

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

    void _set_run_thread_id();

};


#endif //SHAULA_SESSION_H
