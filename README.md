# Shaula

Shaula is a Bitcoin node written in C++.

Asynchronous connections and Multithreading. It uses coroutines, so you don't have to worry about writing callbacks forever.
I'm trying to get an SPV client, but at this point I'm only able to connect to the network.

![shaula.gif](./.assets/shaula.gif)

The default setting is to connect to the test network.
It is accepting connections, but at the moment it is barely functioning because it has not accumulated any blocks.

Currently, everything is deployed in memory, but we plan to write to Redis and other systems in the future.

**The items listed in the Dockerfile are for development purposes only.
Please be careful about security.**

## Examples of usage
Dockerfile is provided for easy develop.
(Please note that this DockerFile is not secure)

In docker-compose.yml, all the files of the project are mounted in /shaula.
You can compile it by entering the container and executing the following in /shaula.

```
mkdir build

cd build

cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++-10 ..

make

./shaula
```

## Dependence


| Name    | URL                                   | Remarks                      |
| --------- | --------------------------------------- | ------------------------------ |
| Boost   | https://github.com/boostorg           | Network, Coroutines, Threads |
| OpenSLL | https://github.com/openssl            | SHA256, RIPEMD-160, Random   |
| Base58  | https://github.com/luke-jr/libbase58  | Base58                       |
| Ncurses | https://invisible-island.net/ncurses/ | CUI Drawing                  |

## Recommended Development Environment

https://www.jetbrains.com/help/clion/remote-projects-support.html

What you need : rsync openssh-server gdb

See DockerFile for details.
