FROM reo7sp/maxbot-cpp
MAINTAINER Oleg Morozenkov <m@oleg.rocks>

WORKDIR /usr/src/echobot
COPY . .
RUN cmake .
RUN make -j4
CMD ./echobot
