//
// GetAddr.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "get_addr.h"

GetAddr::GetAddr(){
    setCommand(CommandDef.GETADDR);
}

void GetAddr::send(boost::asio::ip::tcp::socket &socket, const boost::asio::yield_context &yield) {
    (std::make_unique<GetAddr>())->sendMessage(socket, yield);
}
