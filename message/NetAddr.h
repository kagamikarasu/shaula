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

/**
 * NetAddr Class
 * https://en.bitcoin.it/wiki/Protocol_documentation#Network_address
 * Elements included in the Version and Addr.
 * Note, however, that the elements possessed by Version and Addr are different.
 */
class NetAddr {
    /**
     * unix timestamp
     * ※Not included in the version message
     */
    uint32_t timestamp_{};

    /**
     * Service
     * Define is https://en.bitcoin.it/wiki/Protocol_documentation#version
     */
    uint64_t service_{};

    /**
     * IPv6 Address
     */
    boost::asio::ip::address_v6 address_;

    /**
     * port
     */
    uint16_t port_{};

public:
    /**
     * Constructor for initialization when creating a message.
     * @param bytes
     */
    explicit NetAddr()= default;

    /**
     * Set the addr from the response.
     * The argument must be in the range of addr (30bytes).
     * This constructor only supports the Addr command.
     * @param bytes
     */
    explicit NetAddr(const std::vector<unsigned char> &bytes);

    /**
     * Set the current time
     */
    void setTimestamp();

    /**
     * Set the time of the response result.
     * @param bytes
     */
    void setTimestamp(const std::vector<unsigned char> &&bytes);

    /**
     * Set the service of the this project.
     */
    void setService();

    /**
     * Set the service of the response result.
     */
    void setService(const std::vector<unsigned char> &&bytes);

    /**
     * Set the ipv6 of the this project.
     */
    void setAddr(const Endpoint &endpoint);

    /**
     * Set the ipv6 of the response result.
     * @param bytes
     */
    void setAddr(const std::vector<unsigned char> &&bytes);

    /**
     * Set the port.
     */
    void setPort(const Endpoint &endpoint);

    /**
     * Get a sequence of bytes.
     * @return
     */
    std::vector<unsigned char> getHex();

    /**
     * Get a string of bytes for which there is no timestamp.
     * For Version request (src)
     * @return
     */
    std::vector<unsigned char> getHexNoneTimestamp();

    /**
     * Get the byte sequence with no timestamp and the byte sequence filled with 0x00
     * For Version request (dst)
     * @return
     */
    std::vector<unsigned char> getZeroAddressHex();

    /**
     * Get the string ipv6 address.
     * @return
     */
    std::string getAddressString();

    /**
     * Get ipv6 address.
     * @return
     */
    boost::asio::ip::address_v6 getAddressV6();

    /**
     * Get port number.
     * @return
     */
    uint16_t getPort();
};


#endif //SHAULA_NETADDR_H
