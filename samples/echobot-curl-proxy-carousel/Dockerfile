FROM reo7sp/maxbot-cpp
MAINTAINER Oleg Morozenkov <m@oleg.rocks>

WORKDIR /usr/src/echobot-curl-proxy-carousel
COPY . .
RUN cmake .
RUN make -j4
CMD ./echobot-curl-proxy-carousel
