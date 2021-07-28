//
// Resolver.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include <iostream>
#include "Resolver.h"

std::vector<boost::asio::ip::address_v6> Resolver::getAddresses(const std::string &hostname) {
    boost::asio::io_context resolver_context;

    boost::asio::ip::tcp::resolver resolver_(resolver_context);

    // Although netbase is required, port number 80 is also possible.
    boost::asio::ip::tcp::resolver::query query(hostname, "http");

    // Synchronous execution
    auto results = resolver_.resolve(query);

    // Inspect all DNS results.
    std::vector<boost::asio::ip::address_v6> v6_addresses;
    for(const auto& element : results){
        // Conversion to ipv6
        if(element.endpoint().address().is_v4()){
            v6_addresses.emplace_back(boost::asio::ip::make_address_v6(boost::asio::ip::v4_mapped, element.endpoint().address().to_v4()));
            continue;
        }
        v6_addresses.push_back(element.endpoint().address().to_v6());
    }
    return v6_addresses;
}