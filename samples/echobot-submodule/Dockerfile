FROM reo7sp/tgbot-cpp
MAINTAINER Oleg Morozenkov <a@reo7sp.ru>

WORKDIR /usr/src/echobot-submodule
COPY . .
RUN cmake .
RUN make -j4
CMD ./echobot-submodule
