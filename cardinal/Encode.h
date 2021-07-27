//
// Encode.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_ENCODE_H
#define SHAULA_ENCODE_H

#include <cstdint>
#include <vector>
#include <string>

/**
 * Encode Class
 * It is mainly used to convert from a other types to byte.
 */
class Encode {
public:
    /**
     * int to 2byte hex
     * (Little Endian)
     */
    static std::vector<unsigned char> to2ByteHex(uint16_t n);
    /**
     * int to 4byte hex
     * (Little Endian)
     */
    static std::vector<unsigned char> to4ByteHex(uint32_t);
    /**
     * int to 8byte hex
     * (Little Endian)
     */
    static std::vector<unsigned char> to8ByteHex(uint64_t);
    /**
     * int to byte hex
     * (Little Endian)
     */
    static std::vector<unsigned char> toByteHex(uint64_t n, size_t length);
    /**
     * int to 2byte hex
     * (Big Endian)
     */
    static std::vector<unsigned char> to2ByteHexBig(uint16_t n);
    /**
     * int to byte hex
     * (Big Endian)
     */
    static std::vector<unsigned char> toByteHexBig(uint64_t n, size_t length);
    /**
     * bool to 1byte hex
     * @param b
     * @return
     */
    static unsigned char toByteHex(bool b);
    /**
     * Fill in the specified number of null bytes.
     * (This function actually just turns a string into a sequence of bytes.)
     * @param str
     * @return
     */
    static std::vector<unsigned char> fill(const std::string &str);

    /**
     * Fill in the specified number of null bytes.
     * @param str
     * @param length
     * @return
     */
    static std::vector<unsigned char> fill(const std::string &str, size_t length);
};


#endif //SHAULA_ENCODE_H
