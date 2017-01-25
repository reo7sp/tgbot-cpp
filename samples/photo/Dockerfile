FROM reo7sp/tgbot-cpp
MAINTAINER Oleg Morozenkov <a@reo7sp.ru>

WORKDIR /tmp/photo
COPY . .
RUN cmake .
RUN make -j4
CMD ./photo
