include ../Makefile.defines

PROGS = hostent hostadr daytimetcpcli daytimetcpserv daytimetcpcligetsrv

all: ${PROGS}

hostent: hostent.o
	${CC} ${CFLAGS} -o $@ hostent.o ${LIBS}

hostadr: hostadr.o
	${CC} ${CFLAGS} -o $@ hostadr.o ${LIBS}

daytimetcpcli: daytimetcpcli.o
	${CC} ${CFLAGS} -o $@ daytimetcpcli.o ${LIBS}

daytimetcpserv: daytimetcpserv.o
	${CC} ${CFLAGS} -o $@ daytimetcpserv.o ${LIBS}

daytimetcpcligetsrv: daytimetcpcligetsrv.o
	${CC} ${CFLAGS} -o $@ daytimetcpcligetsrv.o ${LIBS};

clean:
	rm -f ${PROGS} ${CLEANFILES}
