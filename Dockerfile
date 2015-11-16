FROM debian:latest
MAINTAINER Oleg Morozenkov

RUN apt-get update && \
	apt-get install -y g++ make binutils cmake libssl-dev libboost-system-dev libboost-iostreams-dev libboost-test-dev

WORKDIR /tmp/tgbot-cpp
COPY include include
COPY src src
COPY test test
COPY CMakeLists.txt ./
RUN sed -i 's/option(ENABLE_TESTS "Set to ON to enable building of tests" OFF)/option(ENABLE_TESTS "Set to ON to enable building of tests" ON)/g' CMakeLists.txt && \
	cmake . && \
	make -j4 && \
	./TgBot_test && \
	make install  && \
	rm -rf /tmp/tgbot-cpp
