EXENAME=data-parallelism
SRCDIR=../src
CFLAGS=-Wall -I ../inc
CC=gcc
LDFLAGS=-l stdc++
CSRCS=${SRCDIR}/work-pthreads.c \
	${SRCDIR}/main.c
	
#${SRCDIR}/work-sequential.c
	
all:
	${CC} ${CSRCS} ${CFLAGS} -o ${EXENAME} ${LDFLAGS}

clean:
	rm -rf ${EXENAME} *.o

run:
	./${EXENAME}