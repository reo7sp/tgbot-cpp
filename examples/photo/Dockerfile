ARG TGBOT_CPP_IMAGE=reo7sp/tgbot-cpp
FROM ${TGBOT_CPP_IMAGE}
LABEL org.opencontainers.image.authors="Oleg Morozenkov <m@oleg.rocks>"

WORKDIR /usr/src/photo

COPY CMakeLists.txt Makefile ./
COPY src src
COPY example.jpg ./

RUN make install INSTALL_PREFIX=/usr

CMD ["/usr/bin/photo"]
