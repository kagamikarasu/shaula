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
     * Acceptor
     */
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;

    /**
     * Vector with multiple connections
     */
    std::vector<std::unique_ptr<Session>> sessions_;

public:
    /**
     * Prepare available connections.
     * @param io_context
     */
    explicit Server(boost::asio::io_context &io_context);

    /**
     * Prepare listeners.
     */
    void run();
};


#endif //SHAULA_SERVER_H
