FROM reo7sp/tgbot-cpp
MAINTAINER Oleg Morozenkov <m@oleg.rocks>

WORKDIR /usr/src/echobot-webhook-server
COPY . .
RUN cmake .
RUN make -j4
CMD ./echobot-webhook-server
