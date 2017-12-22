include ../Makefile.defines

PROGS = udpcliopt udpcliselect udpclisig

all: ${PROGS}

udpcliopt: udpcli.o dgclitimeopt.o
	${CC} ${CFLAGS} -o $@ udpcli.o dgclitimeopt.o ${LIBS}

udpcliselect: udpcli.o dgclitimeoselect.o
	${CC} ${CFLAGS} -o $@ udpcli.o dgclitimeoselect.o ${LIBS}

udpclisig: udpcli.o dgclitimeosig.o
	${CC} ${CFLAGS} -o $@ udpcli.o dgclitimeosig.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
