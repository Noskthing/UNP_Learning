include ../Makefile.defines

PROGS = hostent hostadr

all: ${PROGS}

hostent: hostent.o
	${CC} ${CFLAGS} -o $@ hostent.o ${LIBS}

hostadr: hostadr.o
	${CC} ${CFLAGS} -o $@ hostadr.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
