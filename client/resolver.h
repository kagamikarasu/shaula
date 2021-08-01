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

/**
 * Resolver Class
 */
class Resolver {
public:
    /**
     * Returns a list of ipv6 addresses from a given hostname.
     * In other words, it expects a response from the DNS server.
     * @param hostname
     * @return
     */
    static std::vector<boost::asio::ip::address_v6> getAddresses(const std::string &hostname);
};

#endif //SHAULA_RESOLVER_H
