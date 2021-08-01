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
#include "cardinal/encode.h"
#include "cardinal/decode.h"
#include "cardinal/crypt.h"

#include "define.h"

struct {
    const int8_t magic = 4;
    const int8_t command = 12;
    const int8_t payload_length = 4;
    const int8_t payload_checksum = 4;
    const int32_t length = 24;
} HeaderSize;

class Header {
    /**
     * Network
     */
    std::vector<unsigned char> magic_;

    /**
     * Command
     * Converting to byte by getHex
     */
    std::string command_;

    /**
     * Payload Length
     * Converting to byte by getHex
     */
    uint32_t payload_length_{};

    /**
     * Payload Checksum
     */
    std::vector<unsigned char> payload_checksum_;
public:
    /**
     * Constructor.
     * set Only Default Network
     */
    explicit Header();

    /**
     * Constructor.
     * set Message Response.
     * @param header_bytes
     */
    explicit Header(const std::vector<unsigned char> &header_bytes);

    /**
     * Set Network
     * @param magic
     */
    void setMagic(const std::vector<unsigned char> &magic);

    /**
     * Set Command from std::string
     * Basically, it is called from the derived class of Message.
     * @param command
     */
    void setCommand(const std::string &command);

    /**
     * Set Command
     * @param command
     */
    void setCommand(const std::vector<unsigned char> &command);

    /**
     * Set Payload Length from Int
     * Basically, it is called from the Message class.
     * @param payload_length
     */
    void setPayloadLength(uint32_t &payload_length);

    /**
     * Set Payload Length
     * @param payload_length
     */
    void setPayloadLength(const std::vector<unsigned char> &payload_length);

    /**
     * Set Payload Checksum
     * Basically, it is called from the Message class.
     * @param payload_checksum
     */
    void setPayloadChecksum(const std::vector<unsigned char> &payload_checksum);

    /**
     * Get Network
     * I don't think I'll ever use it.
     * @return
     */
    std::vector<unsigned char> getMagic();

    /**
     * Get Command(std::string)
     * @return
     */
    std::string getCommand();

    /**
     * Get Payload Length(Int)
     * @return
     */
    uint32_t getPayloadLength();

    /**
     * Get Payload Checksum
     * @return
     */
    std::vector<unsigned char> getPayloadChecksum();

    /**
     * Get the byte sequence of this class (i.e., the header).
     * 24bytes
     * @return
     */
    std::vector<unsigned char> getHex();

    /**
     *
     * @return
     */
    bool isVersion();

    /**
     * Check for Version command.
     * @return
     */
    bool isVerack();

    /**
     * Check for Addr command.
     * @return
     */
    bool isAddr();

    /**
     * Check for GetAddr command.
     * @return
     */
    bool isGetAddr();

    /**
     * Check for Ping command.
     * @return
     */
    bool isPing();

    /**
     * Check for Pong command.
     * @return
     */
    bool isPong();

    /**
     * Check for Mempool command.
     * @return
     */
    bool isMempool();
};


#endif //SHAULA_HEADER_H
