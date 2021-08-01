//
// Server.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_SERVER_H
#define SHAULA_SERVER_H

#include "session.h"

/**
 * Server Class
 * Manage Acceptors
 * Currently, it is a test server.
 */
class Server {
private:
    /**
     * io_context
     */
    std::shared_ptr<boost::asio::io_context> context_server_;

    /**
     * Acceptor
     */
    std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;

    /**
     * Vector with multiple connections
     */
    std::vector<std::shared_ptr<Session>> sessions_;

    /**
     * Number of Thread.
     */
    const static uint8_t number_of_thread_ = 2;

    /**
     * Max Connection.
     */
    const static uint8_t max_connections_ = 10;

public:
    /**
     * Singleton
     * @param io_contexts
     * @return
     */
    static Server* getInstance();

    /**
     * Prepare listeners.
     */
    static void run(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts);

    /**
     * Return Connection List
     * @return
     */
    static std::vector<Session> getConnectionList();

private:
    /**
     * Prepare available connections.
     * @param io_contexts
     */
    Server();

};


#endif //SHAULA_SERVER_H
