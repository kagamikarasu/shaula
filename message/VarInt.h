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

class VarInt {
    unsigned char key_{};
    uint8_t position_{};
    uint64_t length_{};

    /**
     *
     * @param bytes
     */
    void setKey(const std::vector<unsigned char> &bytes);

    /**
     *
     * @param bytes
     */
    void setPosition(uint8_t position);

    /**
     *
     * @param bytes
     */
    void setLength(const std::vector<unsigned char> &bytes);

public:
    explicit VarInt(const std::vector<unsigned char> &bytes){
        setKey(bytes);
        setLength(bytes);
    }

    uint64_t getLength();

    uint8_t getPosition();
};

#endif //SHAULA_VARINT_H
