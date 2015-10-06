#
# Makefile para programas exemplo
#

CC=gcc
LIB_DIR=../lib

all: exemplo mandel teste_vetor teste_prio
	make -C .. libpithread

exemplo: exemplo.c libpithread.a
	$(CC) -g -O0 -o exemplo exemplo.c -L$(LIB_DIR) -lpithread -Wall

teste_vetor: teste_vetor.c libpithread.a
	$(CC) -g -O0 -o teste_vetor teste_vetor.c -L$(LIB_DIR) -lpithread -Wall

teste_prio: teste_prio.c libpithread.a
	$(CC) -g -O0 -o teste_prio teste_prio.c -L$(LIB_DIR) -lpithread -Wall

mandel: mandel.c libpithread.a
	$(CC) -g -O0 -o mandel mandel.c -L$(LIB_DIR) -lpithread -lm -Wall

libpithread.a:
	make -C .. libpithread

clean:
	rm -rf exemplo mandel teste_vetor teste_prio *~
