//
// TestServer.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include <cassert>
#include <cardinal/crypt.h>
#include <cardinal/decode.h>
#include <cardinal/encode.h>

void sha256(){
    auto sha256 = Crypt::sha256(Encode::toBytesFromHexStr("0250863ad64a87ae8a2fe83c1af1a8403cb53f53e486d8511dad8a04887e5b2352"));
    auto sha256_str = Decode::toHexLowerString(sha256);
    assert(strcmp(sha256_str.c_str(), "0b7c28c9b7290c98d7438e70b3d3f7c848fbd7d1dc194ff83f4f7cc9b1378e98") == 0 && "SHA256 Failed");
}

void sha256d(){
    auto sha256d = Crypt::sha256d(Encode::toBytesFromHexStr("00f54a5851e9372b87810a8e60cdd2e7cfd80b6e31"));
    auto sha256d_str = Decode::toHexLowerString(sha256d);
    assert(strcmp(sha256d_str.c_str(), "c7f18fe8fcbed6396741e58ad259b5cb16b7fd7f041904147ba1dcffabf747fd") == 0 && "SHA256 Failed");
}

void base58check(){
    auto base58address = Crypt::getBase58CheckAddress("0250863ad64a87ae8a2fe83c1af1a8403cb53f53e486d8511dad8a04887e5b2352");
    assert(strcmp(base58address.c_str(), "1PMycacnJaSqwwJqjawXBErnLsZ7RkXUAs") == 0 && "Base58Check Failed");
}

int main() {
    sha256();
    sha256d();
    base58check();
    return 0;
}

