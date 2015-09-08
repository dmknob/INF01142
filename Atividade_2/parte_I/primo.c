
/* 
Programa primo.c 

Exemplo de uso de programação concorrente. Analise o que o programa
faz e verifique se ele está correto. Execute mais de uma vez.

Compile com: gcc -o primo primo.c -Wall -lpthread -lm 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h> 

#define MAX 8

int counter = 0;

int isPrime(int num) {
   int i;

   if(num == 0)
     return 1;
   for(i = 2; i <= (int) sqrt((double)num); i++)
       if(num % i == 0) 
         return 0;
   return 1;
}

void *primos(void *id) {
  int i;
  long int limit = (long int) pow(10,5);

  while (counter < limit) {
    counter = counter + 1;
    if (isPrime(counter)) {
       if ( counter % 2 == 0 )
          printf("%8d (id=%1d) PRIMO!?\n", counter, (int)id);
       else
          printf("%8d (id=%1d)", counter, (int)id);
    }
    for (i=0; i < pow(10,5); i++); /*apenas para consumir tempo CPU*/
  }
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t id[MAX];
    int i;

    for(i=0; i < MAX; i++)
       pthread_create(&id[i], NULL, (void *)(primos), (void *) i);

    for(i=0; i < MAX; i++)
      pthread_join(id[i], (void **)NULL);
   
    exit(0);
}
