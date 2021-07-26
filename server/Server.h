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
 *
 */
class Server {
private:

    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
    std::vector<std::unique_ptr<Session>> sessions_;

public:
    explicit Server(boost::asio::io_context &io_context);

    void run();
};


#endif //SHAULA_SERVER_H
