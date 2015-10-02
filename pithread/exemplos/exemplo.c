
/*
 *	Programa de exemplo de uso da biblioteca sthread
 *
 *	Vers�o 1.0 - 25/03/2015
 *
 *	Sistemas Operacionais I - www.inf.ufrgs.br
 *
 */

#include "../include/pithread.h"
#include <stdio.h>

void* func0(void *arg) {
	printf("###-*-*-*-*-*						Eu sou a thread ID0 imprimindo %d\n", *((int *)arg));
	return;
}

void* func1(void *arg) {
	printf("###-*-*-*-*-*						Eu sou a thread ID1 imprimindo %d\n", *((int *)arg));
	return;
}

void* func2(void *arg) {
	printf("###-*-*-*-*-*						Eu sou a thread ID2 imprimindo %d\n", *((int *)arg));
	return;
}

int main(int argc, char *argv[]) {

  int	id0, id1, id2;
	int i = 10;

    id0 = picreate(10, func0, (void *)&i);
		i = 20;
    id1 = picreate(20, func1, (void *)&i);
		i = 30;
		id2 = picreate(30, func2, (void *)&i);
    printf("Eu sou a main apos a criacao de ID0, ID1 e ID2\n");

    printf("piwait id0: %d\n", piwait(id0));
    printf("piwait id1: %d\n", piwait(id1));
		piwait(id2);

    printf("Eu sou a main voltando para terminar o programa\n");

		return 0;
}
