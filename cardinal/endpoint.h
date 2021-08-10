//
// Endpoint.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_ENDPOINT_H
#define SHAULA_ENDPOINT_H

#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/ip/address.hpp"

class Endpoint {
public:
    boost::asio::ip::address local_address;
    boost::asio::ip::address remote_address;
    unsigned short local_port;
    unsigned short remote_port;

    void set(const boost::asio::ip::tcp::socket& socket){
        if(socket.local_endpoint().address().is_v4()){
            local_address = boost::asio::ip::make_address_v6(
                    boost::asio::ip::v4_mapped, socket.local_endpoint().address().to_v4());
        }else{
            local_address = socket.local_endpoint().address().to_v6();
        }

        if(socket.remote_endpoint().address().is_v4()){
            remote_address = boost::asio::ip::make_address_v6(
                    boost::asio::ip::v4_mapped, socket.remote_endpoint().address().to_v4());
        }else{
            remote_address = socket.remote_endpoint().address().to_v6();
        }

        local_port = socket.local_endpoint().port();
        remote_port = socket.remote_endpoint().port();
    }
};


#endif //SHAULA_ENDPOINT_H
