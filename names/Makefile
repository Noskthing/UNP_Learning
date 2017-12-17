include ../Makefile.defines

PROGS = hostent hostadr daytimetcpcli daytimetcpserv daytimetcpcligetsrv daytimeudpcliuncon daytimeudpserv daytimeudpclicon daytimeudpservreuse

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
	${CC} ${CFLAGS} -o $@ daytimetcpcligetsrv.o ${LIBS}

daytimeudpcliuncon: daytimeudpcliuncon.o
	${CC} ${CFLAGS} -o $@ daytimeudpcliuncon.o ${LIBS}

daytimeudpserv: daytimeudpserv.o
	${CC} ${CFLAGS} -o $@ daytimeudpserv.o ${LIBS}

daytimeudpclicon: daytimeudpclicon.o
	${CC} ${CFLAGS} -o $@ daytimeudpclicon.o ${LIBS}

daytimeudpservreuse: daytimeudpservreuse.o udp_server_reuseaddr.o
	${CC} ${CFLAGS} -o $@ daytimeudpservreuse.o udp_server_reuseaddr.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
