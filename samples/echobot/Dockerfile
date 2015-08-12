FROM reo7sp/tgbot-cpp
MAINTAINER Oleg Morozenkov
ENV REFRESHED_AT 2015-08-12

WORKDIR /tmp/echobot
COPY . .
RUN cmake .
RUN make -j4
CMD ./echobot
