//
// config.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_CONFIG_H
#define SHAULA_CONFIG_H

#include <string>
#include <vector>
#include "define.h"

struct ConfigStruct {
    std::vector<unsigned char> NETWORK;
};

class Config {
    ConfigStruct env;

    Config()= default;

    static Config* getConfig(){
        static Config config;
        return &config;
    }

public:
    static void setConfig(const std::string &type){
        auto config = getConfig();

        config->env = {
                {0x0B, 0x11, 0x09, 0x07},
        };

        if(type == "main"){
            config->env.NETWORK = {0xF9, 0xBE, 0xB4, 0xD9};
        }
    }

    static std::vector<unsigned char> getNetwork(){
        auto config = getConfig();
        return config->env.NETWORK;
    }
};

#endif //SHAULA_CONFIG_H
