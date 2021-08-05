//
// Verack.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_VERACK_H
#define SHAULA_VERACK_H

#include "message.h"

/**
 * Verack Class
 * After receiving the Version request, continue to receive the Verack.
 * By receiving the Verack and sending this side too, other commands can be used.
 */
class Verack : public Message{
public:
    /**
     * Constructor
     * There is no payload.
     */
    explicit Verack();

    /**
     * Asynchronous Transfer
     * @param socket
     * @param yield
     */
    static void send(boost::asio::ip::tcp::socket &socket, const boost::asio::yield_context &yield);
};


#endif //SHAULA_VERACK_H
