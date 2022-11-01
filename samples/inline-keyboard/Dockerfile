FROM reo7sp/tgbot-cpp
MAINTAINER Oleg Morozenkov <m@oleg.rocks>

WORKDIR /usr/src/inline-keyboard
COPY . .
RUN cmake .
RUN make -j4
CMD ./inline-keyboard
