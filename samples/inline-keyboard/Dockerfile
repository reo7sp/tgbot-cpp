FROM reo7sp/tgbot-cpp
MAINTAINER Oleg Morozenkov <a@reo7sp.ru>

WORKDIR /usr/src/inline-keyboard
COPY . .
RUN cmake .
RUN make
CMD ./inline-keyboard
