include ../Makefile.defines

PROGS = tcpclinonb tcpclifork daytimetcpclinonb web tcpclirst tcpservselect

all: 	${PROGS}

tcpclinonb: tcpcli.o strclinonb.o
	${CC} ${CFLAGS} -o $@ tcpcli.o strclinonb.o ${LIBS}

tcpclifork: tcpcli.o strclifork.o
	${CC} ${CFLAGS} -o $@ tcpcli.o strclifork.o ${LIBS}

daytimetcpclinonb: daytimetcpclinonb.o
	${CC} ${CFLAGS} -o $@ daytimetcpclinonb.o ${LIBS}

web: web.o home_page.o start_connect.o write_get_cmd.o
	${CC} ${CFLAGS} -o $@ web.o home_page.o start_connect.o \
		write_get_cmd.o ${LIBS}

tcpclirst: tcpclirst.o
	${CC} ${CFLAGS} -o $@ tcpclirst.o ${LIBS}

tcpservselect: tcpservselect.o
	${CC} ${CFLAGS} -o $@ tcpservselect.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
