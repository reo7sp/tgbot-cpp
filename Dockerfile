FROM debian:latest
MAINTAINER Oleg Morozenkov
ENV REFRESHED_AT 2015-08-12

RUN apt-get update && apt-get install -y g++ make binutils cmake libssl-dev libboost-system-dev libboost-iostreams-dev libboost-test-dev

WORKDIR /tmp/tgbot-cpp
COPY include include
COPY src src
COPY CMakeLists.txt ./
RUN cmake .
RUN make -j4
RUN make install
RUN rm -rf /tmp/tgbot-cpp