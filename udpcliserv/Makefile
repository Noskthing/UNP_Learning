include ../Makefile.defines

PROGS = udpserv01 udpcli01 udpcliaddr udpcliconnect udpcliloop udpservloop udpcliipaddr udpservselect

all: 	${PROGS}

udpserv01: 	udpserv01.o
	${CC} ${CFLAGS} -o $@ udpserv01.o ${LIBS}

udpcli01: 	udpcli01.o
	${CC} ${CFLAGS} -o $@ udpcli01.o ${LIBS}

udpcliaddr: udpcliaddr.o dgcliaddr.o
	${CC} ${CFLAGS} -o $@ udpcliaddr.o dgcliaddr.o ${LIBS}

udpcliconnect: udpcli01.o dgcliconnect.o
	${CC} ${CFLAGS} -o $@ udpcli01.o dgcliconnect.o ${LIBS}

udpcliloop: udpcli01.o dgcliloop.o
	${CC} ${CFLAGS} -o $@ udpcli01.o dgcliloop.o ${LIBS}

udpservloop: udpserv01.o dgecholoop.o
	${CC} ${CFLAGS} -o $@ udpserv01.o dgecholoop.o ${LIBS}

udpcliipaddr: udpcliipaddr.o
	${CC} ${CFLAGS} -o $@ udpcliipaddr.o ${LIBS}

udpservselect: udpservselect.o sigchldwaitpid.o
	${CC} ${CFLAGS} -o $@ udpservselect.o sigchldwaitpid.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
