#
# Makefile para programas exemplo
# 

CC=gcc
LIB_DIR=../lib
INC_DIR=../include

all: exemplo mandel teste_vetor teste_prio mutex1 mutex2

exemplo: exemplo.c $(LIB_DIR)/libmthread.a
	$(CC) -o exemplo exemplo.c -L$(LIB_DIR) -I$(INC_DIR) -lmthread -Wall

teste_vetor: teste_vetor.c $(LIB_DIR)/libmthread.a
	$(CC) -o teste_vetor teste_vetor.c -I$(INC_DIR) -L$(LIB_DIR) -lmthread -Wall

teste_prio: teste_prio.c $(LIB_DIR)/libmthread.a
	$(CC) -o teste_prio teste_prio.c -I$(INC_DIR) -L$(LIB_DIR) -lmthread -Wall

mandel: mandel.c $(LIB_DIR)/libmthread.a
	$(CC) -o mandel mandel.c -I$(INC_DIR) -L$(LIB_DIR) -lmthread -lm -Wall

mutex1: mutex1.c $(LIB_DIR)/libmthread.a
	$(CC) -o mutex1 mutex1.c -I$(INC_DIR) -L$(LIB_DIR) -lmthread -Wall

mutex2: mutex2.c $(LIB_DIR)/libmthread.a
	$(CC) -o mutex2 mutex2.c -I$(INC_DIR) -L$(LIB_DIR) -lmthread -Wall

run:
	@echo "---Exemplo------------------------------------------\r\n"
	exemplo
	sleep 4
	@echo "---Teste Vetor---------------------------------------\r\n"
	teste_vetor
	sleep 4
	@echo "---Teste Prio----------------------------------------\r\n"
	teste_prio
	sleep 4
	@echo "---Mutex 1 -------------------------------------------\r\n"
	mutex1
	sleep 4
	@echo "---Mutex 2 -------------------------------------------\r\n"
	mutex2
	sleep 4
	@echo "---Mandel --------------------------------------------\r\n"
	mandel -p
	eog mandel.ppm &


clean:
	rm -rf exemplo mandel teste_vetor teste_prio mutex1 mutex2 mandel.ppm *~ *.o




