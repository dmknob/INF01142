/****
 * file queuer.c
 *
   Program to demonstrate the thread management package *
   Written by Douglas Jones, Sept 7, 2001               *
                                                     ****/

#include <stdio.h>
#include "threads.h"

static struct thread_semaphore data, free;

void producer(int i)
{
        int j;
	printf( "Enter produce %1d", i );
        for (j = 1; j < 6; j++) {
                thread_wait( &free );
                printf( "produce %1d", i );
                thread_signal( &data );
        }
}

void consumer(int i)
{
	printf( "Enter consume %1d", i );
        for (;;) {
                thread_wait( &data );
                printf( "consume %1d", i );
                thread_signal( &free );
        }
}

main()
{
        printf("Iniciando!\n");
        thread_manager_init();
        printf("Iniciado!\n");
        thread_semaphore_init( &data, 0 );
        printf("semaphore init!\n");
        thread_semaphore_init( &free, 3 );
        thread_launch( 4000, producer, 1 );
        printf("launch 1!\n");
        thread_launch( 4000, producer, 2 );
        printf("launch 2!\n");
        thread_launch( 4000, consumer, 1 );
        printf("launch 3!\n");
        thread_launch( 4000, consumer, 2 );
        printf("launch 4!\n");
        thread_manager_start();
        printf("manager start!\n");
}
