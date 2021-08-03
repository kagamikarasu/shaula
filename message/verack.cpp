//
// Verack.hpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "verack.h"

Verack::Verack() {
    setCommand(CommandDef.VERACK);
}