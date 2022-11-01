FROM reo7sp/tgbot-cpp
MAINTAINER Oleg Morozenkov <m@oleg.rocks>

WORKDIR /usr/src/echobot-curl-client
COPY . .
RUN cmake .
RUN make -j4
CMD ./echobot-curl-client
