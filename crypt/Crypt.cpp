//
// Crypt.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Crypt.h"

std::vector<unsigned char> Crypt::sha256(const std::vector<unsigned char> &bytes) {
    std::vector<unsigned char> vec;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, bytes.data(), bytes.size());
    SHA256_Final(hash, &sha256);
    for(unsigned char & i : hash){
        vec.push_back(i);
    }
    return vec;
}

std::vector<unsigned char> Crypt::sha256d(const std::vector<unsigned char> &bytes) {
    return sha256(sha256(bytes));
}

std::vector<unsigned char> Crypt::ripemd160(const std::vector<unsigned char> &bytes) {
    std::vector<unsigned char> vec;
    static unsigned char hash[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160_CTX ripemd;
    RIPEMD160_Init(&ripemd);
    RIPEMD160_Update(&ripemd, bytes.data(), bytes.size());
    RIPEMD160_Final(hash, &ripemd);

    for(unsigned char & i : hash){
        vec.push_back(i);
    }
    return vec;
}

std::string Crypt::getBase58CheckAddress(const std::vector<unsigned char> &bytes) {
    unsigned char version_byte = 0x00;

    // 1. sha256
    std::vector<unsigned char> en0 = sha256(bytes);
    // 2. ripemd160
    std::vector<unsigned char> en1 = ripemd160(en0);

    // 3. add version byte
    std::vector<unsigned char> en2 = en1;
    en2.insert(en2.begin(), version_byte);

    // 4. sha256 double
    std::vector<unsigned char> en3 = sha256d(en2);

    // 5. 2.result + 4.result(lead 4 bytes)
    std::vector<unsigned char> en4 = en2;
    for( int i = 0 ; i < 4 ; i++){
        en4.push_back(en3[i]);
    }
    // 6. b58encode
    auto en5 = toBase58Check(en4);

    // return std::string
    return std::string(en5.begin(), en5.end());
}

std::string Crypt::getBase58CheckAddress(const std::string &hex_bin){
    std::vector<unsigned char> vec = toHexFromHexStr(hex_bin);
    return getBase58CheckAddress(vec);
}

std::vector<char> Crypt::toBase58Check(const std::vector<unsigned char> &bytes) {
    size_t b58size = bytes.size()*2;
    std::shared_ptr<char> b58_ptr = std::make_shared<char>(bytes.size());

    bool re_bol = b58enc(b58_ptr.get(), &b58size, bytes.data(), bytes.size());

    std::vector<char> base58_vec(b58size);
    char* vc_ptr = b58_ptr.get();
    for(int i = 0 ; i < b58size ; i++){
        base58_vec[i] = *vc_ptr;
        vc_ptr++;
    }
    return base58_vec;
}

std::vector<unsigned char> Crypt::toHexFromHexStr(const std::string &hex_bin) {
    std::vector<unsigned char> bytes;
    for (unsigned int i = 0; i < hex_bin.length(); i += 2) {
        std::string byteString = hex_bin.substr(i, 2);
        char byte = (char) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

std::vector<unsigned char> Crypt::getRand(uint16_t size){
    unsigned char nonce[size];
    RAND_bytes(nonce, size);
    return { nonce, nonce + size };
}