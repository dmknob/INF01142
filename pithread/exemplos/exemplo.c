
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
	printf("		###-*-*-*-*-*				Eu sou a thread ID1 imprimindo %d\n", *((int *)arg));
	*(int *)arg = *(int *)arg -1;
	//printf("%d\n", *(int *)arg);
}

void* func1(void *arg) {
	printf("		###-*-*-*-*-*				Eu sou a thread ID2 imprimindo %d\n", *((int *)arg));
	*(int *)arg = *(int *)arg -2;
}

void* func2(void *arg) {
	printf("		###-*-*-*-*-*				Eu sou a thread ID3 imprimindo %d\n", *((int *)arg));
	*(int *)arg = *(int *)arg -3;
}

int main(int argc, char *argv[]) {

  int	id1, id2, id3, id4;
	int i = 20;

    id1 = picreate(20, func0, (void *)&i);
    id2 = picreate(10, func1, (void *)&i);
		id3 = picreate(5, func2, (void *)&i);
		printf("Eu sou a main apos a criacao de ID1, ID2 e ID3\n");
    printf("piwait id1: %d\n", piwait(id1));
    //id4 = picreate(25, func2, (void *)&i);
		printf("piwait id2: %d\n", piwait(id2));
		piwait(id3);
		//piwait(id4);
		//id0 = picreate(5, func0, (void *)&i);
		//piwait(id0);
    printf("Eu sou a main voltando para terminar o programa. %d\n", i);

		return 0;
}
