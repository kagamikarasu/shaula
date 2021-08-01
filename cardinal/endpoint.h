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

#include "boost/asio/ip/address.hpp"

typedef struct {
    boost::asio::ip::address local_address{};
    boost::asio::ip::address remote_address{};
    unsigned short local_port{};
    unsigned short remote_port{};
} Endpoint;
#endif //SHAULA_ENDPOINT_H
