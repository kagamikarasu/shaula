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
#include "crypt/Crypt.h"
#include "cardinal/Encode.h"
#include "cardinal/Endpoint.h"
#include "Define.h"
#include "Header.h"
#include "NetAddr.h"
#include "VarInt.h"

class Message {

protected:
    std::unique_ptr<Header> header_;
    std::vector<unsigned char> payload_;

public:
    Message():
        header_(std::make_unique<Header>()){}

    explicit Message(Header &header){
        header_ = std::make_unique<Header>(header);
    }

    Message(const Header &header, const std::vector<unsigned char> &body) {
        header_ = std::make_unique<Header>(header);
        payload_ = body;
    }

    /**
     *
     */
    void setPayload(std::vector<unsigned char>);

    /**
     *
     * @return
     */
    virtual std::vector<unsigned char> getMessage();

    /**
     *
     * @return
     */
    std::vector<unsigned char> getHeader();

    /**
     *
     * @return
     */
    std::vector<unsigned char> getBody();

private:
    void setLength();
    void setChecksum();

protected:
    void setCommand(std::string &command_name);
    std::string getCommand();

};


#endif //SHAULA_MESSAGE_H
