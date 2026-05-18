FROM reo7sp/maxbot-cpp
MAINTAINER Oleg Morozenkov <m@oleg.rocks>

WORKDIR /usr/src/received-text-processing
COPY . .
RUN cmake .
RUN make -j4
CMD ./received-text-processing
