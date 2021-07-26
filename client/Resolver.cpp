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

std::vector<boost::asio::ip::address_v6> Resolver::getAddresses(boost::asio::io_context &ioContext, const std::string &hostname) {
    boost::asio::ip::tcp::resolver resolver_(ioContext);
    boost::asio::ip::tcp::resolver::query query(hostname, "http");
    auto results = resolver_.resolve(query);

    std::vector<boost::asio::ip::address_v6> v6_addresses;
    for(const auto& element : results){
        if(element.endpoint().address().is_v4()){
            v6_addresses.emplace_back(boost::asio::ip::make_address_v6(boost::asio::ip::v4_mapped, element.endpoint().address().to_v4()));
            continue;
        }
        v6_addresses.push_back(element.endpoint().address().to_v6());
    }
    return v6_addresses;
}