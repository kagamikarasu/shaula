//
// Message.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_MESSAGE_H
#define SHAULA_MESSAGE_H

#include <vector>
#include <chrono>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include "cardinal/crypt.h"
#include "cardinal/encode.h"
#include "cardinal/endpoint.h"
#include "config/define.h"
#include "header.h"
#include "struct/net_addr.h"
#include "struct/var_str.h"
#include "struct/var_int.h"

/**
 * Message Class (Base)
 * Use this class as the base class and create a derived class corresponding to the command.
 * In the derived class, after overloading setCommand and setPayload, you can get the byte string by calling getMessage.
 */
class Message {
private:
    /**
     * Header Instance
     * Only Command is operable.
     * Please check setCommand().
     */
    std::unique_ptr<Header> header_;

    /**
     * Payload (std::vector<unsigned>)
     * Basically, create a derived class and set the message
     */
    std::vector<unsigned char> payload_;

public:
    /**
     * Constructor when creating a new message
     */
    explicit Message();

    /**
     * Constructor to receive the response for now.
     * Basically, it should not be used.
     * @param header
     * @param body
     */
    explicit Message(const Header &header, const std::vector<unsigned char> &body);

    /**
     * Obtain messages that can be sent to the network.
     * Header and payload are included.
     * @return
     */
    virtual std::vector<unsigned char> getMessage();

    std::vector<unsigned char> getBodyHeadBytes();

private:
    /**
     * Set Header
     * @param header
     */
    void setHeader(const Header &header);

    /**
     * Set Length
     */
    void setLength();

    /**
     * Set Checksum
     */
    void setChecksum();

protected:
    /**
     * Set the command in the header.
     * Wants to be called from a derived class
     * @param command_name
     */
    void setCommand(const char* &command_name);

    /**
     * Set the payload.
     * Wants to be called from a derived class
     * @param bytes
     */
    void setPayload(const std::vector<unsigned char> &bytes);

    /**
     * Asynchronous Transfer
     * @param socket
     * @param yield
     */
    void sendMessage(boost::asio::ip::tcp::socket &socket, const boost::asio::yield_context &yield);
};


#endif //SHAULA_MESSAGE_H
