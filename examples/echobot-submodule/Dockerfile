ARG TGBOT_CPP_IMAGE=reo7sp/tgbot-cpp
FROM ${TGBOT_CPP_IMAGE}
LABEL org.opencontainers.image.authors="Oleg Morozenkov <m@oleg.rocks>"

WORKDIR /usr/src/tgbot-cpp

COPY CMakeLists.txt ./
COPY cmake cmake
COPY include include
COPY src src

WORKDIR /usr/src/echobot-submodule

COPY examples/echobot-submodule/CMakeLists.txt examples/echobot-submodule/Makefile ./
COPY examples/echobot-submodule/src src

RUN make install \
        INSTALL_PREFIX=/usr \
        TGBOT_CPP_SOURCE_DIR=/usr/src/tgbot-cpp

CMD ["/usr/bin/echobot-submodule"]
