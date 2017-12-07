include ../Makefile.defines

all: ${LIB_OBJS} 
	ar rv ../libunp.a $?
	${RANLIB} ${LIBUNP_NAME}

clean:
	rm -f ${CLEANFILES}
