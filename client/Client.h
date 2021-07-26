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

class Client : public Node {
    boost::asio::ip::address_v6 address_;
    uint16_t port_;
    uint32_t protocol_version_{};
    uint32_t service_{};
public:
    explicit Client(boost::asio::io_context &io_context, boost::asio::ip::address_v6 address, uint16_t port);

    void run();

    bool isOpen();

private:
    void _run(const boost::asio::yield_context &yield);
    void _connect(const boost::asio::yield_context &yield);
    void _receive(const boost::asio::yield_context &yield);
    void _close();
};

#endif //SHAULA_CLIENT_H
