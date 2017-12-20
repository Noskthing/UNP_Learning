include ../Makefile.defines

PROGS = daytimetcpsrvdaemon daytimetcpsrvinetd

all: 	${PROGS}

daytimetcpsrvdaemon: daytimetcpsrvdaemon.o
	${CC} ${CFLAGS} -o $@ daytimetcpsrvdaemon.o ${LIBS}

daytimetcpsrvinetd: daytimetcpsrvinetd.o
	${CC} ${CFLAGS} -o $@ daytimetcpsrvinetd.o ${LIBS} 

clean:
	rm -f ${PROGS} ${CLEANFILES}
