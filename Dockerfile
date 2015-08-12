FROM debian:latest
MAINTAINER Oleg Morozenkov

RUN apt-get update && apt-get install g++ make binutils cmake libssl-dev libboost-system-dev libboost-iostreams-dev libboost-test-dev

WORKDIR /tmp/tgbot
COPY include ./
COPY src ./
COPY CMakeLists.txt ./
RUN cmake .
RUN make -j4
RUN make install
RUN rm -rf /tmp/tgbot