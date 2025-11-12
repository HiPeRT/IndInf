# For C language
CSRCS=../src/circular_array.c \
	../test/main.cpp	
CC=gcc

# For C++ language
#CSRCS=../src/circular_array.cpp \
	../test/main.cpp
#CC=g++

CFLAGS=-Wall -I../inc
EXENAME=test
LDFLAGS=

all:
	${CC} ${CSRCS} ${CFLAGS} -o ${EXENAME} ${LDFLAGS}

clean:
	rm -rf ${EXENAME} *.o