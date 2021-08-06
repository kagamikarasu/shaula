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

/**
 * Decode Class
 * It is mainly used to convert from a byte to other types.
 */
class Decode {
public:
    /**
     * Hex to byte int
     * (Little Endian)
     * @param bytes
     * @return
     */
    static int32_t toByteInt(const std::vector<unsigned char> &bytes);

    /**
     * Hex to byte int
     * (Big Endian)
     * @param bytes
     * @return
     */
    static int32_t toByteIntBig(const std::vector<unsigned char> &bytes);

    /**
     * Returns a string, ignoring the null byte sequence
     * @param str
     * @return
     */
    static std::string unFillToString(const std::vector<unsigned char> &str);

    /**
     * Convert a byte to a string (HEX Upper)
     * @param bytes
     * @return
     */
    static std::string toHexUpperString(const std::vector<unsigned char> &bytes);

    /**
     * Convert a byte to a string (HEX Lower)
     * @param bytes
     * @return
     */
    static std::string toHexLowerString(const std::vector<unsigned char> &bytes);
};

#endif //SHAULA_DECODE_H
