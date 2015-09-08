CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TST_DIR=./testes

all: teste1.x

teste1.x:
	$(CC) -o teste1.x teste1.c -L../lib -lpithread -Wall

lista1:
	$(CC) -o lista1.x lista1.c -Wall

clean:
	rm -rf *.x *.o
	ls -R
