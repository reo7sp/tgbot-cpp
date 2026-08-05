ARG TGBOT_CPP_IMAGE=reo7sp/tgbot-cpp
FROM ${TGBOT_CPP_IMAGE}
LABEL org.opencontainers.image.authors="Oleg Morozenkov <m@oleg.rocks>"

WORKDIR /usr/src/tgbot-cpp

COPY CMakeLists.txt ./
COPY cmake cmake
COPY include include
COPY src src

WORKDIR /usr/src/echobot-submodule

COPY examples/echobot-submodule/CMakeLists.txt ./
COPY examples/echobot-submodule/src src

RUN cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DTGBOT_CPP_SOURCE_DIR=/usr/src/tgbot-cpp
RUN cmake --build build --parallel $(nproc)
RUN cmake --install build --prefix /usr --component example

CMD ["/usr/bin/echobot-submodule"]
