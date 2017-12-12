include ../Makefile.defines

PROGS = tcpserv01 tcpcli01 tcpservfork

all: ${PROGS}

tcpcli01 : tcpcli01.o
	${CC} ${CFLAGS} -o $@ tcpcli01.o ${LIBS}

tcpserv01 : tcpserv01.o
	${CC} ${CFLAGS} -o $@ tcpserv01.o ${LIBS}
tcpservfork : tcpservfork.o sigchldwaitpid.o
	${CC} ${CFLAGS} -o $@ tcpservfork.o sigchldwaitpid.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
