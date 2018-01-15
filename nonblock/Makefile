include ../Makefile.defines

PROGS = tcpclinonb tcpclifork

all: 	${PROGS}

tcpclinonb: tcpcli.o strclinonb.o
	${CC} ${CFLAGS} -o $@ tcpcli.o strclinonb.o ${LIBS}

tcpclifork: tcpcli.o strclifork.o
	${CC} ${CFLAGS} -o $@ tcpcli.o strclifork.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
