/*Teste com vetor de listas*/
/*vetorlistas.c*/

#include "../include/pithread.h"
#include "../include/pidata.h"
#include <stdlib.h>
#include <stdio.h>

TCB_t *aptos;
int contador = 0;

TCB_t * aloca(void){
  TCB_t *novo = (TCB_t *) malloc(sizeof (TCB_t));
  if(!novo){
    printf("Sem memoria disponivel!\n");
    exit(-1);
  }
  else{
    novo->tid = contador;
    novo-> state = 0;
    novo->credCreate = 100 - (5 * contador);
    novo->credReal = 100 - (5 * contador);
    novo->next = NULL;
    novo->prev = NULL;
    contador = contador + 1;
    //printf("CredReal%d\n", novo->CredReal);
  }
  return novo;
}

int insere(TCB_t *novo){
  //if( aptos->CredReal)
  TCB_t *temp;
  //temp = aloca();
  temp = aptos;
  while (temp->next != NULL){
    printf("%p\n",temp->next);
    if (novo->credReal < aptos->credReal){
      printf("credReal: %d\n", temp->credReal);
    }
    temp=temp->next;
  }
  //printf("%p\n", novo->next);
  /*if (novo->credReal < aptos->credReal){
    temp=aptos;
    aptos = novo;
    novo = temp;
  }*/
  //printf("aptos Real: %d\n", aptos->credReal);
  //printf("novo Real: %d\n", novo->credReal);
  return 0;
}

int main(int argc, char const *argv[]){
  printf("\n\n\n\n\n");

  aptos = (TCB_t *) malloc(sizeof (TCB_t));
  TCB_t *novo;
  printf("Init!\n");
  //novo = aloca();
  aptos = aloca();
  printf("%d\n", aptos->tid);
  printf("Real: %d\n", aptos->credReal);
  novo = aloca();
  aptos->next = novo;
  novo = aloca();
  aptos->next->next = novo;
  insere(aloca());
  /*aptos = novo;
  printf("Create: %d\n", aptos->credCreate);
  novo = aloca();
  aptos->next = novo;
  printf("Real: %d\n", aptos->next->credReal);
  aptos->next->next = aloca();
  printf("Real: %d\n", aptos->next->next->credReal);
  aptos->next->next->next = aloca();
  printf("Real: %d\n", aptos->next->next->next->credReal);
  */
  /*printf("Endereco prim: %p\n", &primeiro);
  printf("Endereco prim: %p\n", primeiro->next);
  printf("Endereco prim: %p\n", primeiro);
  printf("Endereco aptos: %p\n", aptos);
  printf("Endereco next: %p\n", aptos->next);
  printf("%d\n", sizeof(aptos));
  printf("%d\n", sizeof(*aptos));
  printf("%d\n", sizeof(primeiro));
  printf("%d\n", sizeof(*primeiro));
  printf("%d\n", sizeof(aptos->next));
  aptos->next = primeiro;
  printf("Endereco next: %p\n", &(aptos->next));
  */
  //(*aptos)->next = primeiro;
  //aptos->next->next = aloca;
  //printf("Endereco NN: %p\n", *aptos->next->next);
  //printf("Endereco NNN: %p\n", *aptos->next->next->next);

  /*struct TCB_t* principal;
  principal = (struct TCB_t *) malloc(sizeof (TCB_t));
  if(!principal){
		printf("Sem memoria disponivel!\n");
		exit(-1);
	}
  else{
    printf("Endereco: %p\n", principal);
  }
  printf("Endereco: %d\n", principal->tid);
  printf("Endereco aptos: %p\n", aptos);
  printf("aptos: %d\n", *aptos);
  printf("aptos: %p\n", &aptos);
  /*
  main->state = 1;
  main->credCreate = 31;
  main->credReal = 31;
  main->next = NULL;
  printf("Pointer *: %p\n", (void *)&main);
  printf("Pointer: %p\n", *main);
  printf("Endereco: %p\n", aptos[31]);
  printf("Cred: %d\n", main->credReal);
  printf("Cred *: %p\n", (void *)main->credReal);

  if (aptos[main->credReal] = NULL)
  {
    printf("Entrei no IF\n");
    aptos[(main->credReal)] = &main;
  }
  else
  {
    printf("Nao entrei no IF\n");
    aptos[(main->credReal)]->next = *main;
  }
  printf("Endereco: %p\n", aptos[31]);
  */
  //printf("Cred: %d\n", aptos[main->credReal]->credReal);
  //printf("Pointer: %p\n", aptos[30]);
/*
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
  */
  return 0;
}
