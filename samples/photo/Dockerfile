FROM reo7sp/maxbot-cpp
MAINTAINER Oleg Morozenkov <m@oleg.rocks>

WORKDIR /usr/src/photo
COPY . .
RUN cmake .
RUN make -j4
CMD ./photo
