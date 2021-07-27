//
// Client.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_CLIENT_H
#define SHAULA_CLIENT_H

#include "Node.h"
#include "crypt/Crypt.h"

/**
 *
 */
class Client : public Node {
    boost::asio::ip::address_v6 address_;
    uint16_t port_;
    uint32_t protocol_version_{};
    uint32_t service_{};
public:
    /**
     * Constructor.
     * Specify the ipv6 address (boost) and port number of the connection destination.
     * @param io_context
     * @param address
     * @param port
     */
    explicit Client(boost::asio::io_context &io_context, boost::asio::ip::address_v6 address, uint16_t port);

    /**
     * Start a new coroutine and make a connection.
     * It sends and receives data asynchronously.
     */
    void run();

    /**
     * Check if the connection is maintained.
     * @return
     */
    bool isOpen();

private:
    /**
     * Running the run method.
     * After sending the connection check and version message, wait for data reception.
     * Please check Node for the receiving behavior.
     * @param yield
     */
    void _run(const boost::asio::yield_context &yield);

    /**
     * Initiates asynchronous connection and reception.
     * @param yield
     */
    void _connect(const boost::asio::yield_context &yield);

    /**
     * Start receiving.
     * @param yield
     */
    void _receive(const boost::asio::yield_context &yield);

    /**
     * Disconnects the connection and removes itself from the connection pool.
     * At the same time, it starts a new connection.
     * See ClientPool.h for more details.
     */
    void _close();
};

#endif //SHAULA_CLIENT_H
