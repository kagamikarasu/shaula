//
// Header.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_HEADER_H
#define SHAULA_HEADER_H

#include <vector>
#include "crypt/Crypt.h"
#include "cardinal/Encode.h"
#include "cardinal/Decode.h"
#include "Define.h"

struct {
    const int8_t magic = 4;
    const int8_t command = 12;
    const int8_t payload_length = 4;
    const int8_t payload_checksum = 4;
    const int32_t length = magic + command + payload_length + payload_checksum;
} HeaderSize;

class Header {
    std::vector<unsigned char> magic_;
    std::string command_;
    uint32_t payload_length_{};
    std::vector<unsigned char> payload_checksum_;
public:
    /**
     *
     */
    explicit Header():
        // Payload checksum
        payload_checksum_(HeaderSize.payload_checksum, 0x00)
    {
        setMagic(versionMeta.NETWORK);
    }

    /**
     *
     * @param header_bytes
     */
    explicit Header(std::vector<unsigned char> header_bytes);

    /**
     *
     * @param magic
     */
    void setMagic(std::vector<unsigned char> magic);

    /**
     *
     * @param command
     */
    void setCommand(std::string &command);

    /**
     *
     * @param command
     */
    void setCommand(std::vector<unsigned char> &command);

    /**
     *
     * @param payload_length
     */
    void setPayloadLength(uint32_t &payload_length);

    /**
     *
     * @param payload_length
     */
    void setPayloadLength(std::vector<unsigned char> &payload_length);

    /**
     *
     * @param payload_checksum
     */
    void setPayloadChecksum(std::vector<unsigned char> payload_checksum);

    /**
     *
     * @return
     */
    std::vector<unsigned char> getMagic();

    /**
     *
     * @return
     */
    std::string getCommand();

    /**
     *
     * @return
     */
    uint32_t getPayloadLength();

    /**
     *
     * @return
     */
    std::vector<unsigned char> getPayloadChecksum();

    /**
     *
     * @return
     */
    std::vector<unsigned char> getHex();

    /**
     *
     * @return
     */
    bool isVersion();

    /**
     *
     * @return
     */
    bool isVerack();

    /**
     *
     * @return
     */
    bool isAddr();

    /**
     *
     * @return
     */
    bool isGetAddr();

    /**
     *
     * @return
     */
    bool isPing();

    /**
     *
     * @return
     */
    bool isPong();

    bool isMempool();
};


#endif //SHAULA_HEADER_H
