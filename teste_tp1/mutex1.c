#include "mthread.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 100
#define MAX_WORK 1000

mmutex_t mutex;
int workDone = 0;
int lastWork = -1;

void *makeWork()
{
	myield();
	while(workDone < MAX_WORK)
	{
		mlock(&mutex);
		lastWork = workDone;
		workDone++;
		munlock(&mutex);
		if (workDone <= lastWork || workDone -1 != lastWork)
		{
			puts("Mutual Exclusion error!!!!!!!");
			printf("%d -> %d\n", lastWork, workDone);
			exit(0);
		}
		if (workDone < MAX_WORK)
		{
			printf("Work #%d done.\n", workDone);
			myield();
		}
	}
        return (NULL);
}

int main ()
{
	int ids[MAX_THREADS];
	int i = 0;

	puts ("Started.");

        mmutex_init(&mutex);

	for (i=0; i < MAX_THREADS; i++)
	{
		ids[i] = mcreate(2,&makeWork, NULL);
		printf("Thread using TID %d started working...\n", ids[i]);
	}

	for (i=0; i < MAX_THREADS; i++)
	{
		mwait(ids[i]);
		printf("Thread using TID %d finished.\n", ids[i]);
	}

	exit(0);
}
