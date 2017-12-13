include ../Makefile.defines

PROGS = udpserv01 udpcli01 udpcliaddr udpcliconnect

all: 	${PROGS}

udpserv01: 	udpserv01.o
	${CC} ${CFLAGS} -o $@ udpserv01.o ${LIBS}

udpcli01: 	udpcli01.o
	${CC} ${CFLAGS} -o $@ udpcli01.o ${LIBS}

udpcliaddr: udpcliaddr.o dgcliaddr.o
	${CC} ${CFLAGS} -o $@ udpcliaddr.o dgcliaddr.o ${LIBS}

udpcliconnect: udpcli01.o dgcliconnect.o
	${CC} ${CFLAGS} -o $@ udpcli01.o dgcliconnect.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
