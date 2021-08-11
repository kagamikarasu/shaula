//
// last_send.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_LAST_SEND_H
#define SHAULA_LAST_SEND_H

#include <message/header.h>

class LastSend {
private:
    /**
     * Header
     */
    std::unique_ptr<Header> header_;

public:
    /**
     * Set Header
     * @param header
     */
    void setHeader(const Header& header);

    /**
     * Get Header
     * @return
     */
    Header& getHeader();
};


#endif //SHAULA_LAST_SEND_H
