//
// Decode.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_DECODE_H
#define SHAULA_DECODE_H

#include <vector>
#include <cmath>

class Decode {
public:
    /**
     * Hex to byte int
     * (Little Endian)
     */
    static int32_t toByteInt(std::vector<unsigned char>);

    static std::string unFillToString(const std::vector<unsigned char> &str);
};


#endif //SHAULA_DECODE_H
