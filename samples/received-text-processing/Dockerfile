FROM reo7sp/tgbot-cpp
MAINTAINER Oleg Morozenkov <a@reo7sp.ru>

WORKDIR /usr/src/received-text-processing
COPY . .
RUN cmake .
RUN make -j4
CMD ./received-text-processing
