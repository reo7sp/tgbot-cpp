ARG TGBOT_CPP_IMAGE=reo7sp/tgbot-cpp
FROM ${TGBOT_CPP_IMAGE}
LABEL org.opencontainers.image.authors="Oleg Morozenkov <m@oleg.rocks>"

WORKDIR /usr/src/photo

COPY CMakeLists.txt ./
COPY src src
COPY example.jpg ./

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --parallel $(nproc)
RUN cmake --install build --prefix /usr

CMD ["/usr/bin/photo"]
