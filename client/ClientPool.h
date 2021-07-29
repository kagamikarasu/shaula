//
// ClientPool.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_CLIENTPOOL_H
#define SHAULA_CLIENTPOOL_H

#include "Resolver.h"
#include "Client.h"
#include <unordered_map>

/**
 * Singleton class for connection management
 * Possesses the connected list and the unconnected list,
 * and tries to connect to another node when disconnected from the client
 */
class ClientPool {
private:
    /**
     * List of connections in progress
     */
    std::map<std::string, Client> connection_pool_;

    /**
     * List of unconnected
     */
    std::unordered_map<std::string, std::uint16_t> unused_pool_;

    /**
     * pool locker
     */
    bool lock_ = false;

    /**
     * Singleton
     */
    ClientPool()= default;

public:
    /**
     * Singleton
     * @return
     */
    static ClientPool* getInstance();

    /**
     * Add Connection From Domain
     * Ex. Use DNS Server
     * @param io_context
     * @param dns_address
     * @param port
     */
    static void add(std::vector<std::shared_ptr<boost::asio::io_context>> &io_context, const std::string &dns_address, uint16_t port);

    /**
     * Add Connection From NetAddrVector
     * Use Addr Response
     * @param io_context
     * @param endpoint_list
     */
    static void add(boost::asio::io_context &io_context, const std::vector<NetAddr> &endpoint_list);

    /**
     * Add a connection from an ipv6 address
     * If the number of connections exceeds the limit,
     * it is added to the unused pool. If the number is not exceeded, add the connection to the connection pool.
     * @param io_context
     * @param address
     * @param port
     */
    static void add(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address, uint16_t port);

    /**
     * Check MaxConnection
     * @return
     */
    static bool isMaxConnection();

    /**
     * When ConnectionPoolElement is closed,
     * delete it and retrieve it from unusedList to make a connection.
     * @param io_context
     */
    [[deprecated("Please use pullUp()")]]
    static void resize(boost::asio::io_context &io_context);

    /**
     * Removes the specified address from the pool.
     * Then, use io_context to start a connection from the unused pool.
     * @param io_context
     * @param address
     */
    static void pullUp(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address);

    /**
     * Return the list of currently connected clients.
     * @return
     */
    static std::map<std::string, Client> getConnectionList();

private:
    /**
     * Run ConnectionPoolElement
     * @param address
     */
    void _run(const std::string &address);

};


#endif //SHAULA_CLIENTPOOL_H
