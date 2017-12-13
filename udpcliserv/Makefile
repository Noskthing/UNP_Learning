include ../Makefile.defines

PROGS = udpserv01 udpcli01 udpcliaddr

all: 	${PROGS}

udpserv01: 	udpserv01.o
	${CC} ${CFLAGS} -o $@ udpserv01.o ${LIBS}

udpcli01: 	udpcli01.o
	${CC} ${CFLAGS} -o $@ udpcli01.o ${LIBS}

udpcliaddr: udpcliaddr.o dgcliaddr.o
	${CC} ${CFLAGS} -o $@ udpcliaddr.o dgcliaddr.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
