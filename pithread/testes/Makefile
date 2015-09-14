CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TST_DIR=./testes

all: libpithread teste1.x

teste1.x: libpithread
	$(CC) -o teste1.x teste1.c -L../lib -lpithread -Wall

libpithread:
	make -C .. libpithread

lista1:
	$(CC) -o lista1.x lista1.c -Wall

clean:
	rm -rf *.x *.o
	ls -R
