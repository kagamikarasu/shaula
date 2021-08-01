//
// Crypt.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_CRYPT_H
#define SHAULA_CRYPT_H

#include <vector>
#include <memory>
#include <string>
#include <cstring>
#include <libbase58.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <openssl/rand.h>

/**
 * Crypt Class
 * You can get SHA256(+double) / ripemd160 / BASE58 / random from any byte sequence.
 */
class Crypt {
public:
    /**
     * bytes -> sha256 hash
     * @param bytes
     * @return
     */
    static std::vector<unsigned char> sha256(const std::vector<unsigned char> &bytes);

    /**
     * bytes -> sha256(sha256 hash)
     * @param bytes
     * @return
     */
    static std::vector<unsigned char> sha256d(const std::vector<unsigned char> &bytes);

    /**
     * bytes -> bytes ripemd160
     * @param messages
     * @return
     */
    static std::vector<unsigned char> ripemd160(const std::vector<unsigned char> &bytes);

    /**
     * bytes -> base58address
     * @param pubkey
     * @param size
     * @return
     */
    static std::string getBase58CheckAddress(const std::vector<unsigned char> &bytes);

    /**
     * pubKey stringHex -> base58address
     * @param hex_bin
     * @return
     */
    static std::string getBase58CheckAddress(const std::string &hex_bin);

    /**
     * bytes -> bytes base58encode
     * @param version
     * @param bytes
     * @param size
     * @return
     */
    static std::vector<char> toBase58Check(const std::vector<unsigned char> &bytes);

    /**
     * Convert StringHex -> Vector<unsigned char>
     * @param hex_bin
     * @return
     */
    static std::vector<unsigned char> toHexFromHexStr(const std::string &hex_bin);

    /**
     * Returns a random value with as many digits as the specified number.
     * Mainly when you want a nonce value.
     * @param size
     * @return
     */
    static std::vector<unsigned char> getRandNonce(uint16_t size);
};

#endif //SHAULA_CRYPT_H
