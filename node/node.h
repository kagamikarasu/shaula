//
// Node.h
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
#include "cardinal/endpoint.h"
#include "message/message.h"
#include "message/version.h"
#include "message/verack.h"
#include "message/addr.h"
#include "message/get_addr.h"
#include "message/ping.h"
#include "message/pong.h"
#include "message/mempool.h"
#include "message/header.h"

class Node {
protected:
    boost::asio::io_context& io_context_;
    std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
    std::shared_ptr<boost::asio::streambuf> receive_buffer_;
    Endpoint endpoint_;

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
     * Set Local Address & Remote Address
     * For Version/GetAddr...etc
     */
    void setAddr();

    /**
     * Send Version Command (Assumed Get Version)
     * @param yield
     */
    void sendVersion(const boost::asio::yield_context &yield);

    /**
     * Send Verack Command (Assumed Receive Verack)
     * @param yield
     */
    void sendVerack(const boost::asio::yield_context &yield);

    /**
     * Send Raw (test)
     * @param yield
     * @param hex_str
     */
    void sendRaw(const boost::asio::yield_context &yield, const std::string &hex_str);

    /**
     * Send GetAddr Command (Assumed Get Addr)
     * @param yield
     */
    void sendGetAddr(const boost::asio::yield_context &yield);

    /**
     * Send Ping Command (Assumed Get Pong)
     * @param yield
     */
    void sendPing(const boost::asio::yield_context &yield);

    /**
     * Send Pong Command (Assumed Receive Ping)
     * second args bytes is ping nonce value
     * @param yield
     * @param bytes
     */
    void sendPong(const boost::asio::yield_context &yield, const std::vector<unsigned char> &bytes);

    /**
     * Send Mempool Command (Assumed Get Inv)
     * Only Remote Node Service is BLOOM
     * @param yield
     */
    void sendMempool(const boost::asio::yield_context &yield);
};


#endif //SHAULA_NODE_H
