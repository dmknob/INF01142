CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TST_DIR=./testes

all: libpithread teste1.x

teste1.x: libpithread
	$(CC) -o teste1.x teste1.c -L../lib -lpithread -Wall

filas.x: libpithread
	$(CC) -o filas.x filas.c -L../lib -lpithread -Wall

lista1.x: libpithread
	$(CC) -o lista1.x lista1.c  -L../lib -lpithread -Wall

lista_1.x: libpithread
	$(CC) -o lista_1.x lista_1.c  -L../lib -lpithread -Wall

vetorlistas.x: libpithread
	$(CC) -o vetorlistas.x vetorlistas.c  -L../lib -lpithread -Wall

libpithread:
	make -C .. libpithread

clean:
	rm -rf *.x *.o
	ls -R
