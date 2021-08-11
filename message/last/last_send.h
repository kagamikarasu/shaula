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

#include "message/header.h"

class LastSend {
private:
    /**
     * Header
     */
    std::unique_ptr<Header> header_;

    /**
     * True: implement the Verack response.
     * False: do not perform the Verack response.
     *
     * Enable after sending the Version Message.
     * Disable the Verack Message after receiving it.
     */
    bool isAlreadyVerack = false;

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

    /**
     * Enable after sending the Version Message.
     */
    void enableVerack();

    /**
     * Disable the Verack Message after receiving it.
     */
    void disableVerack();

    /**
     * Returns the current state.
     * @return
     */
    bool isEnableVerack();

    /**
     * Check header pointer
     * @return
     */
    bool hasHeader();
};


#endif //SHAULA_LAST_SEND_H
