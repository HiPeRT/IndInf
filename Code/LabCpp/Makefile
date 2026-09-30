EXENAME=hello
CSRCS=src/ciao.cpp src/stampa.cpp src/operazioni.cpp
LDFLAGS=-l stdc++

all:
	gcc ${CSRCS} ${LDFLAGS} -o ${EXENAME}

run: hello
	./${EXENAME}

clean:
	rm -f ${EXENAME}
	rm -g *.o
