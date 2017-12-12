include ../Makefile.defines

PROGS = tcpcliselect tcpservselect tcpservpoll

all: 	${PROGS}

tcpcliselect: 	tcpcliselect.o strcliselect.o
			${CC} ${CFLAGS} -o $@ tcpcliselect.o strcliselect.o ${LIBS}

tcpservselect: tcpservselect.o
	${CC} ${CFLAGS} -o $@ tcpservselect.o ${LIBS}

tcpservpoll: tcpservpoll.o
	${CC} ${CFLAGS} -o $@ tcpservpoll.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
