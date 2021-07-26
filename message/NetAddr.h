//
// NetAddr.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_NETADDR_H
#define SHAULA_NETADDR_H

#include <vector>
#include <cstdint>
#include "cardinal/Endpoint.h"
#include "cardinal/Encode.h"
#include "cardinal/Decode.h"
#include "Define.h"

class NetAddr {
    uint32_t timestamp_{};
    uint64_t service_{};
    boost::asio::ip::address_v6 address_;
    uint16_t port_{};

public:
    explicit NetAddr()= default;

    explicit NetAddr(const std::vector<unsigned char> &bytes);

    void setTimestamp();

    void setTimestamp(const std::vector<unsigned char> &&bytes);

    void setService();

    void setService(const std::vector<unsigned char> &&bytes);

    void setAddr(Endpoint&);

    void setAddr(const std::vector<unsigned char> &&bytes);

    void setPort(Endpoint&);

    std::vector<unsigned char> getHex();

    std::vector<unsigned char> getHexNoneTimestamp();

    std::vector<unsigned char> getZeroAddressHex();

    std::string getAddressString();

    boost::asio::ip::address_v6 getAddressV6();

    uint16_t getPort();
};


#endif //SHAULA_NETADDR_H
