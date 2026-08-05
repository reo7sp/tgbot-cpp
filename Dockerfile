FROM debian:trixie AS builder

RUN apt-get -qq update && \
    apt-get -qq install -y \
        build-essential \
        cmake \
        g++-13 \
        gcc-13 \
        ninja-build \
        python3 \
        python3-pip \
        python3-venv && \
    rm -rf /var/lib/apt/lists/*

ENV CC="gcc-13"
ENV CXX="g++-13"
ENV CONAN_BUILD_ARGS="--build=never"

RUN python3 -m venv /opt/conan && \
    /opt/conan/bin/pip install --no-cache-dir "conan==2.31.1"
ENV PATH="/opt/conan/bin:${PATH}"

WORKDIR /usr/src/tgbot-cpp

COPY conanfile.py Makefile ./

RUN make dependencies

COPY include include
COPY src src
COPY cmake cmake
COPY CMakeLists.txt ./

RUN make install INSTALL_PREFIX=/usr DESTDIR=/tmp/tgbot-cpp-install


FROM debian:trixie AS runtime
LABEL org.opencontainers.image.authors="Oleg Morozenkov <m@oleg.rocks>"

COPY --from=builder /tmp/tgbot-cpp-install/usr /usr
