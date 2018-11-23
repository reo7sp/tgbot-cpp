FROM ubuntu:14.04
MAINTAINER Oleg Morozenkov <a@reo7sp.ru>

RUN apt-get -qq update && \
    apt-get -qq install -y g++ make binutils cmake libssl-dev libcurl4-openssl-dev

RUN apt-get -qq update && \
    apt-get -qq install -y wget build-essential python-dev autotools-dev libicu-dev libbz2-dev zlib1g-dev

WORKDIR /usr/src/boost
RUN wget -q -O boost_1_59_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.gz/download && \
    tar xzf boost_1_59_0.tar.gz && \
    rm boost_1_59_0.tar.gz && \
    cd boost_1_59_0 && \
    ./bootstrap.sh --prefix=/usr/ --with-libraries=system,test && \
    ./b2 -j $(nproc) -d0 && \
    ./b2 install && \
    cd .. && \
    rm -r boost_1_59_0


WORKDIR /usr/src/tgbot-cpp
COPY include include
COPY src src
COPY test test
COPY CMakeLists.txt ./

RUN cmake -DENABLE_TESTS=ON . && \
    make -j$(nproc) && \
    make install


COPY samples samples

WORKDIR /usr/src/tgbot-cpp/samples/echobot
RUN rm -rf CMakeCache.txt CMakeFiles/ && \
    cmake . && make -j$(nproc)

WORKDIR /usr/src/tgbot-cpp/samples/echobot-curl-client
RUN rm -rf CMakeCache.txt CMakeFiles/ && \
    cmake . && make -j$(nproc)

WORKDIR /usr/src/tgbot-cpp/samples/echobot-webhook-server
RUN rm -rf CMakeCache.txt CMakeFiles/ && \
    cmake . && make -j$(nproc)

WORKDIR /usr/src/tgbot-cpp/samples/inline-keyboard
RUN rm -rf CMakeCache.txt CMakeFiles/ && \
    cmake . && make -j$(nproc)

WORKDIR /usr/src/tgbot-cpp/samples/photo
RUN rm -rf CMakeCache.txt CMakeFiles/ && \
    cmake . && make -j$(nproc)


WORKDIR /usr/src/tgbot-cpp
ENV CTEST_OUTPUT_ON_FAILURE=1
CMD make test

