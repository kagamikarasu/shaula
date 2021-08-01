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
#include "Encode.h"
#include "Decode.h"

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

    explicit VarInt() = default;

    /**
     * The argument is a string of bytes that VarInt will start with.
     * The first byte stores the actual data read start position in "position_".
     * Also, the actual data size is stored in "length_".
     * Used to receive requests.
     * @param bytes
     */
    explicit VarInt(const std::vector<unsigned char> &bytes);

    /**
     * !!!!!!!Needs to be fixed.!!!!!!!!!!
     * This constructor is for VarStr.
     * Currently, only 1 byte size (255 length) is supported.
     * Used to send a request.
     * @param str
     */
    explicit VarInt(const std::string &str);

    /**
     * Get the start reading position.
     * @return
     */
    uint8_t getPosition();

    /**
     * Get Body Length.
     * @return
     */
    uint64_t getBodyLength();

    /**
     * Get Payload Length
     * @return
     */
    uint64_t getPayloadLength();

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
