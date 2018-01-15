include ../Makefile.defines

PROGS = tcpclinonb

all: 	${PROGS}

tcpclinonb: tcpcli.o strclinonb.o
	${CC} ${CFLAGS} -o $@ tcpcli.o strclinonb.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
