ARG TGBOT_CPP_IMAGE=reo7sp/tgbot-cpp
FROM ${TGBOT_CPP_IMAGE}
LABEL org.opencontainers.image.authors="Oleg Morozenkov <m@oleg.rocks>"

RUN apt-get -qq update && \
    apt-get -qq install -y \
        build-essential \
        cmake \
        libboost-dev \
        libcurl4-openssl-dev \
        nlohmann-json3-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/reply-keyboard

COPY examples/reply-keyboard/CMakeLists.txt ./
COPY examples/reply-keyboard/src src

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --parallel $(nproc)
RUN cmake --install build --prefix /usr --component example

CMD ["/usr/bin/reply-keyboard"]
