# Shaula

Shaula is a Bitcoin node.

I'm trying to get an SPV client, but at this point I'm only able to connect to the network.


## How To Use

```
mkdir build

cd build

cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++-10 ..

make

./shaula
```

## Recommended development environment

Full Remote Debug

https://www.jetbrains.com/help/clion/remote-projects-support.html

Use : rsync openssh-server gdb

See DockerFile for details.
