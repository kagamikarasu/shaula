//
// Resolver.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_RESOLVER_H
#define SHAULA_RESOLVER_H

#include <string>
#include <boost/asio/ip/tcp.hpp>

class Resolver {
public:
    static std::vector<boost::asio::ip::address_v6> getAddresses(boost::asio::io_context &ioContext, const std::string &hostname);
};


#endif //SHAULA_RESOLVER_H
