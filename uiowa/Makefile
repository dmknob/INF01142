#
# Makefile ESQUELETO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# NECESSARIO adaptar este esqueleto de makefile para suas necessidades.
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "pithread"
#

CC=gcc
LIB_DIR=./lib
BIN_DIR=./bin

all: libthreads example1 example2
#	make -C testes all

libthreads: threads.o
	ar crs $(LIB_DIR)/libthreads.a $(BIN_DIR)/threads.o

threads.o:
	$(CC) -o $(BIN_DIR)/threads.o -c threads.c -Wall

example1: libthreads
	$(CC) -o example1.x example1.c -L./lib -lthreads -Wall

example2: libthreads
	$(CC) -o example2.x example2.c -L./lib -lthreads -Wall

#regra1: #dependências para a regra1
#	$(CC) -o $(BIN_DIR)regra1 $(SRC_DIR)regra1.c -Wall

#regra2: #dependências para a regra2
#	$(CC) -o $(BIN_DIR)regra2 $(SRC_DIR)regra2.c -Wall

#regran: #dependências para a regran
#	$(CC) -o $(BIN_DIR)regran $(SRC_DIR)regran.c -Wall

clean:
	rm -rf *.a *.o *.x
	ls -R
