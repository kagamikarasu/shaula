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
     * Number of threads to use
     */
    const static uint8_t number_of_thread_ = 15;

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
     * @param dns_address
     * @param port
     */
    static void add(const std::string &dns_address, uint16_t port);

    /**
     * Add Connection From NetAddrVector
     * Use Addr Response
     * @param io_context
     * @param endpoint_list
     */
    static void add(boost::asio::io_context &io_context, const std::vector<NetAddr> &endpoint_list);

    /**
     * Retrieve addresses from the unconnected pool and store them in the thread pool.
     * @param io_contexts
     */
    static void run(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts);

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
     * Add to connected pool.
     * @param io_context
     * @param address
     * @param port
     */
    void _addCPool(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address, uint16_t port);

    /**
     * Add to unconnected pool.
     * @param address
     * @param port
     */
    void _addUPool(const std::string &address, uint16_t port);

    /**
     * Remove from the unconnected pool and put into the connected pool
     * @param io_context
     */
    void _pullUp(boost::asio::io_context &io_context);

    /**
     * Remove from connected pool.
     * @param address
     */
    void _removeCPool(const boost::asio::ip::address_v6 &address);

    /**
     * Block until unconnected list is accumulated.
     */
    void _emptyPoolBlock();

    /**
     * Lock pool operations to prevent conflicts.
     * Blocked until other threads are completed.
     */
    void _lock();

    /**
     * Unlock
     */
    void _unlock();

};


#endif //SHAULA_CLIENTPOOL_H
