//
// VarInt.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_VARINT_H
#define SHAULA_VARINT_H

#include <cstdint>
#include <vector>
#include "cardinal/Encode.h"
#include "cardinal/Decode.h"

/**
 * VarInt Class
 * Variable Length Int
 * https://en.bitcoin.it/wiki/Protocol_documentation#Variable_length_integer
 */
class VarInt {
    /**
     * First Byte Value.
     * It doesn't make any sense.
     */
    unsigned char key_{};

    /**
     * Start position for reading the payload.
     */
    uint8_t position_{};

    /**
     * Payload length.
     */
    uint64_t length_{};


public:
    /**
     * The argument is a string of bytes that VarInt will start with.
     * The first byte stores the actual data read start position in "position_".
     * Also, the actual data size is stored in "length_".
     * @param bytes
     */
    explicit VarInt(const std::vector<unsigned char> &bytes);

    /**
     * Get the start reading position.
     * @return
     */
    uint8_t getPosition();

    /**
     * Get Payload Length.
     * @return
     */
    uint64_t getLength();

private:
    /**
     * It doesn't make any sense.
     * @param bytes
     */
    void setKey(const std::vector<unsigned char> &bytes);

    /**
     * Get the length of the Payload Length being used from the first byte (VariableInt),
     * and set the read start position and Payload length.
     * @param bytes
     */
    void setPosition(uint8_t position);

    /**
     * Set Payload Length
     * @param bytes
     */
    void setLength(const std::vector<unsigned char> &bytes);
};

#endif //SHAULA_VARINT_H
