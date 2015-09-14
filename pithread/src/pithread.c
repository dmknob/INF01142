#include "../include/pithread.h"
#include "../include/pidata.h"
#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>

int inicializada = -1; //Marca se a biblioteca já foi inicializada.
int id;
ucontext_t context, thrcontext; //Armazena o contexto
TCB_t *TCBmain ; //Declara o TCB da thread main
TCB_t *TCBnew ; //Declara o TCB da thread main
char thr_stack[SIGSTKSZ];

int picreate (int credCreate, void* (*start)(void*), void *arg)
{
  printf("DBG - chamado picriate(). ID: %d\n", id);
  if (inicializada != 0) //Primeira chamada a funcao.
  {
    printf("DBG - Inicializando biblioteca - thread main.\n");
    TCBmain = (TCB_t *) malloc(sizeof(TCB_t)); //Aloca TCB da main
    getcontext(&context); //Salva o contexto da main
    //*/Ajusta o TCB da main/*/
    TCBmain->tid = 0;
    TCBmain->state = 0; //Criada
    //TCBmain->context = context;
    TCBmain->credCreate = 100;
    TCBmain->credReal = 100;
    TCBmain->context = context;
    TCBmain->next = NULL;
    printf("Contexto da main construido.\n");
    //*/Ajusta o TCB da main/*/
    //getcontext(&context); //Salva o contexto da main
    printf("Primeiro ID: %d\n", id);
    inicializada = 0;
  }

  printf("Executando picreate na biblioteca. Creditos: %d\n", credCreate);
  id = id+1;
  TCBnew = (TCB_t *) malloc(sizeof(TCB_t)); //Aloca um novo TCB
  TCBnew->tid = id;
  TCBnew->state = 0;
  TCBnew->credCreate = credCreate;
  TCBnew->credReal = credCreate;
  TCBnew->context = context;
  TCBnew->prev = TCBmain;
  TCBnew->next = NULL;
  //getcontext(&context); //Salva o contexto da main
  getcontext(&thrcontext);
  //thrcontext.uc_link = NULL;
  thrcontext.uc_link = &context;
  thrcontext.uc_stack.ss_sp = thr_stack;
  thrcontext.uc_stack.ss_size = sizeof(thr_stack);
  makecontext(&thrcontext, (void (*)(void)) start, 1, arg);
  swapcontext(&context, &thrcontext);
  //setcontext(&thrcontext);

  //TCBmain->context = context;
  //setcontext(&context);
  printf("Saindo do create() com ID=%d\n", id);
  return id;
}

int piyield(void)
{
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}
int piwait(int tid)
{
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}
int pimutex_init(pimutex_t *mtx)
{
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}
int pilock (pimutex_t *mtx)
{
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}
int piunlock (pimutex_t *mtx)
{
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}
