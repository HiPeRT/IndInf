EXENAME=hello
CSRCS=hello.cpp stampa/stampa.cpp
LDFLAGS=-l stdc++

all:
	gcc ${CSRCS} ${LDFLAGS} -o ${EXENAME}

run: hello
	./${EXENAME}

clean:
	rm -f ${EXENAME}
	rm -g *.o