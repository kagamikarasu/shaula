//
// node.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_NODE_H
#define SHAULA_NODE_H

#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/thread.hpp>
#include "cardinal/endpoint.h"
#include "listener/listener_if.h"
#include "listener/listener_version.h"
#include "listener/listener_verack.h"
#include "listener/listener_ping.h"
#include "listener/listener_addr.h"


class Node {
private:
    /**
     * Receive Buffer
     */
    boost::asio::streambuf receive_buffer_;

protected:
    /**
     * IO CONTEXT
     */
    boost::asio::io_context& io_context_;

    /**
     * Socket
     */
    boost::asio::ip::tcp::socket socket_;

    /**
     * Deadline Timer
     */
    boost::asio::deadline_timer timeout_;

    /**
     * Connection Address
     */
    Endpoint endpoint_;

    /**
     * Run ThreadID
     */
    std::string run_thread_id_;

    /**
     * Last send
     */
    LastSend last_send_;

    /**
     * Last received
     */
    LastRecv last_recv_{};

    /**
     * Listener List
     */
    std::vector<std::unique_ptr<ListenerIF>> listeners_;

public:

    /**
     * Return the last received.
     * @return
     */
    LastRecv& getLastRecv();

    /**
     * Return the Struct.
     * @return
     */
    NodeStruct getStruct();

    /**
     * Returns the thread ID that this node is currently running on.
     */
    std::string getRunThreadId();

    /**
     * Add Listener
     */
    void addListener(std::unique_ptr<ListenerIF> listener);

    /**
     * Check if the socket is open.
     * @return
     */
    bool isOpen();

    /**
     * Close the socket.
     * Override destination for details
     */
    virtual void close();

protected:
    /**
     * Constructor
     * @param io_context
     */
    explicit Node(boost::asio::io_context& io_context);

    /**
     * Get Header From Buffer
     * @param yield
     * @return
     */
    std::unique_ptr<Header> getHeader(const boost::asio::yield_context& yield);

    /**
     * Get Body From Buffer
     * @param yield
     * @param header
     * @return
     */
    std::vector<unsigned char> getBody(const boost::asio::yield_context &yield, Header &header);

    /**
     * Set tun threadId
     */
    void setRunThreadId();

    /**
     * Set DefaultListener
     */
    void setDefaultListener();
};


#endif //SHAULA_NODE_H
