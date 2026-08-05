FROM debian:trixie AS dependencies

RUN apt-get -qq update && \
    apt-get -qq install -y \
        build-essential \
        cmake \
        libboost-dev \
        libcurl4-openssl-dev \
        nlohmann-json3-dev && \
    rm -rf /var/lib/apt/lists/*


FROM dependencies AS builder

WORKDIR /usr/src/tgbot-cpp

COPY include include
COPY src src
COPY cmake cmake
COPY CMakeLists.txt Makefile ./

RUN make install-with-system INSTALL_PREFIX=/usr DESTDIR=/tmp/tgbot-cpp-install


FROM dependencies AS runtime
LABEL org.opencontainers.image.authors="Oleg Morozenkov <m@oleg.rocks>"

COPY --from=builder /tmp/tgbot-cpp-install/usr /usr
