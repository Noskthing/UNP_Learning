include ../Makefile.defines

PROGS = udpserv01 udpcli01

all: 	${PROGS}

udpserv01: 	udpserv01.o
	${CC} ${CFLAGS} -o $@ udpserv01.o ${LIBS}

udpcli01: 	udpcli01.o
	${CC} ${CFLAGS} -o $@ udpcli01.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
