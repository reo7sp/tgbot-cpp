FROM debian:latest
MAINTAINER Oleg Morozenkov <m@oleg.rocks>

RUN apt-get -qq update && \
    apt-get -qq install -y g++ make binutils cmake libssl-dev libboost-system-dev libcurl4-openssl-dev zlib1g-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/tgbot-cpp
COPY include include
COPY src src
COPY CMakeLists.txt ./

RUN cmake . && \
    make -j$(nproc) && \
    make install && \
    rm -rf /usr/src/tgbot-cpp/*
