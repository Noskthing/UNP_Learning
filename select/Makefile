include ../Makefile.defines

PROGS = tcpcliselect tcpservselect

all: 	${PROGS}

tcpcliselect: 	tcpcliselect.o strcliselect.o
			${CC} ${CFLAGS} -o $@ tcpcliselect.o strcliselect.o ${LIBS}

tcpservselect: tcpservselect.o
	${CC} ${CFLAGS} -o $@ tcpservselect.o ${LIBS}


clean:
	rm -f ${PROGS} ${CLEANFILES}
