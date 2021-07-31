FROM ubuntu:20.04

RUN apt update && \
    apt install -y gcc-10 g++-10 cmake libboost-dev libssl-dev netbase libncurses-dev libboost-thread-dev libboost-coroutine-dev libbase58-dev rsync openssh-server gdb && \
    mkdir /run/sshd && \
    echo 'root:root' | chpasswd && \
    sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY .docker/sshd/sshd_config /etc/ssh/sshd_config

EXPOSE 22 8333 18333

CMD ["/usr/sbin/sshd", "-D"]