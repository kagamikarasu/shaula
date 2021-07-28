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

#include "Session.h"

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
    std::vector<std::unique_ptr<Session>> sessions_;

public:
    /**
     * Prepare listeners.
     */
    static void run(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts);

private:
    /**
     * Prepare available connections.
     * @param io_contexts
     */
    explicit Server(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts);

    /**
     * Singleton
     * @param io_contexts
     * @return
     */
    static Server* getInstance(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts);
};


#endif //SHAULA_SERVER_H
