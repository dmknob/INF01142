/*

	A ideia desse teste é criar uma thread na main que aponta para function1.
	Na function1, cria-se mais MAX_THREADS threads, cada uma redirecionando para function2.
	Na function2, cria-se mais MAX_THREADS threads, cada uma redirecionando para function3.
	Na function3, cada thread imprime um valor no visor. Esse valor é incrementado a cada thread que é criada.

*/


#include "mthread.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 10

mmutex_t mutex1, mutex2;
int threadCounter = 0;

void *function3()
{
	myield();
	printf("%d\n", threadCounter);
	return NULL;
}

void *function2()
{
	int threads[MAX_THREADS];
	int i = 0;
	
	for (i = 0; i < MAX_THREADS; i++)
	{
		mlock(&mutex2);
		threadCounter++;
		munlock(&mutex2);
		threads[i] = mcreate(1, &function3, NULL);
		myield();
	}
	return NULL;
}

void *function1()
{
	int threads[MAX_THREADS];
	int i = 0;

        mmutex_init(&mutex1);
        mmutex_init(&mutex2);

	for (i = 0; i < MAX_THREADS; i++)
	{
		mlock(&mutex1);
		threadCounter++;
		munlock(&mutex1);
		threads[i] = mcreate(1, &function2, NULL);
	}

	for (i = 0; i < MAX_THREADS; i++)
	{
		mwait(threads[i]);
	}

	return NULL;
}

int main ()
{
	int mainThread;
	mmutex_init(&mutex1);
	mmutex_init(&mutex2);

	mainThread = mcreate(1, &function1, NULL);
	mwait(mainThread);
	
	return 0;
}
