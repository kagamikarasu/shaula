//
// VarStr.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_VARSTR_H
#define SHAULA_VARSTR_H

#include "VarInt.h"

class VarStr {
    /**
     * See VarInt
     */
    VarInt var_int_;

    /**
     * Actual string data
     * VarInt is not included.
     */
    std::vector<unsigned char> body_;

public:
    explicit VarStr() = default;

    /**
     * Used when a message is received.
     * The argument should contain VarInt at the beginning.
     * @param bytes
     */
    explicit VarStr(const std::vector<unsigned char> &bytes);

    /**
     * Used for sending.
     * Does not need to contain VarInt.
     * @param str
     */
    explicit VarStr(const std::string &str);

    /**
     * Get the Vector string.
     * VarInt is not included.
     * @return
     */
    std::vector<unsigned char> getBody();

    /**
     * Get the string.
     * VarInt is not included.
     * @return
     */
    std::string getBodyString();

    /**
     * Returns the number of character bytes.
     * VarInt values are not included.
     * Equivalent to VarInt::getBodyLength.
     * @return
     */
    uint64_t getBodyLength();

    /**
     * Returns the total length containing the VarInt values.
     * Equivalent to VarInt::getPayloadLength.
     * @return
     */
    uint64_t getPayloadLength();

    /**
     * Get the Payload.
     * Contains a VarInt.
     * @return
     */
    std::vector<unsigned char> getPayload();
};

#endif //SHAULA_VARSTR_H
