include ../Makefile.defines

PROGS = hostent

all: ${PROGS}

hostent: hostent.o
	${CC} ${CFLAGS} -o $@ hostent.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
