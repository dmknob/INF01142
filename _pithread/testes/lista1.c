/*Primeiro teste com listas*/
/*lista1.c*/

#include "../include/pithread.h"
#include "../include/pidata.h"
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char const *argv[])
{
  TCB_t *Lista = (TCB_t *) malloc(sizeof (TCB_t));
  if(!Lista){
		printf("Sem memoria disponivel!\n");
		exit(-1);
	}
  Lista->next = NULL; //Inicializa a lista

 //Aloca mais 1 nodo
  TCB_t *thread1 = (TCB_t *) malloc(sizeof(TCB_t));
  if(!thread1){
		printf("Sem memoria disponivel!\n");
		exit(-1);
	}
  thread1->next = NULL;

//Encadeia
  Lista->next = thread1;

//inicializa dados do TCB desta thread
  Lista->next->tid=0;
  Lista->next->state=1;
  Lista->next->credCreate=100;
  Lista->next->credReal=Lista->next->credCreate;

//Aloca
  TCB_t *thread2 = (TCB_t *) malloc(sizeof(TCB_t)); //Aloca mais 1 nodo
  if(!thread2){
		printf("Sem memoria disponivel!\n");
		exit(-1);
	}
  thread2->next = NULL;

//encadeia
  Lista->next->next = thread2;

//inicializa dados do TCB desta thread
  Lista->next->next->tid=1;
  Lista->next->next->state=2;
  Lista->next->next->credCreate=50;
  Lista->next->next->credReal=Lista->next->next->credCreate;

  printf("TID1 %d\n", Lista->next->tid);
  printf("TID2 %d\n", Lista->next->next->tid);
  printf("credReal1  %d\n", Lista->next->credReal);
  printf("credReal2  %d\n", Lista->next->next->credReal);

  free(thread2);
  free(thread1);
  free(Lista);
  return 0;
}
