//
// Addr.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_ADDR_H
#define SHAULA_ADDR_H


#include "message.h"

/**
 * Addr is GetAddr Response.
 */
class Addr : public Message {
    std::unique_ptr<VarInt> var_int_;
    std::vector<NetAddr> addrList_;

public:
    /**
     * Constructor
     * The bytes argument wants the result of the response body
     * @param bytes
     */
    explicit Addr(const std::vector<unsigned char> &bytes);

    /**
     * Setter for variable (VarInt) Class, read from the beginning by giving the bytes column and set accordingly.
     * See VarInt Class for details.
     * @param bytes
     */
    void setVarInt(const std::vector<unsigned char> &bytes);

    /**
     * The value is set by giving the response byte string.
     * ※Since it refers to VarInt, it must be set beforehand.
     * @param bytes
     */
    void setAddrList(const std::vector<unsigned char> &bytes);

    /**
     * Return Addr as Vector
     * @return
     */
    std::vector<NetAddr> getAddrList();

    /**
     * Display All Addr List
     */
    void showAddrList();
};


#endif //SHAULA_ADDR_H
