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
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TST_DIR=./testes

all: libpithread

libpithread: pithread.o listmanager.o
	ar crs $(LIB_DIR)/libpithread.a $(BIN_DIR)/pithread.o $(BIN_DIR)/listmanager.o

pithread.o:
	$(CC) -g -O0 -o $(BIN_DIR)/pithread.o -c $(SRC_DIR)/pithread.c -Wall

listmanager.o:
	$(CC) -g -O0 -o $(BIN_DIR)/listmanager.o -c $(SRC_DIR)/listmanager.c -Wall

regra1: #dependências para a regra1
	$(CC) -o $(BIN_DIR)regra1 $(SRC_DIR)regra1.c -Wall

regra2: #dependências para a regra2
	$(CC) -o $(BIN_DIR)regra2 $(SRC_DIR)regra2.c -Wall

regran: #dependências para a regran
	$(CC) -o $(BIN_DIR)regran $(SRC_DIR)regran.c -Wall

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(TST_DIR)/*.x $(TST_DIR)/*.o  $(SRC_DIR)/*~ $(INC_DIR)/*~ *~
	ls -R
