FROM debian:stretch
MAINTAINER Oleg Morozenkov <a@reo7sp.ru>

RUN apt-get -qq update && \
	apt-get -qq install -y g++ make binutils cmake libssl-dev libboost-system-dev

WORKDIR /tmp/tgbot-cpp
COPY include include
COPY src src
COPY CMakeLists.txt ./

RUN cmake . && \
	make -j4 && \
	make install && \
	rm -rf /tmp/tgbot-cpp/*
