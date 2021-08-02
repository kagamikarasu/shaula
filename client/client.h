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

#include "node/node.h"

/**
 *
 */
class Client : public Node {

    /**
     * Address being connected
     */
    boost::asio::ip::address_v6 address_;

    /**
     * Port being connected
     */
    uint16_t port_;

    /**
     * Last received header
     */
    std::shared_ptr<Header> last_receive_header_;

    /**
     * Last received body head body
     */
    std::vector<unsigned char> last_receive_body_head_;

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
     * Returns the last received Header.
     * If this function is read before receiving, a temporary value is returned.
     * @return
     */
    std::shared_ptr<Header> getLastReceiveHeader();


    /**
     * Get the first few bytes of the Body.
     * Uppercase
     * @return
     */
    std::string getLastReceiveBodyHead();

    /**
     * Disconnects the connection and removes itself from the connection pool.
     * At the same time, it starts a new connection.
     * See ClientPool.h for more details.
     */
    void close() override;

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
};

#endif //SHAULA_CLIENT_H
