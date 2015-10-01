#include "../include/pithread.h"
//#include "../include/pidata.h"
#include "../include/listmanager.h"
//#include <ucontext.h>
//#include <stdlib.h>
//#include <stdio.h>

int inicializada = -1; //Marca se a biblioteca já foi inicializada.
int id = 0;
ucontext_t context, thrcontext; //Armazena o contexto
//TCB_t *TCBmain = NULL; //Declara o TCB da thread main
TCB_t *tcb[15];
//TCB_t *tcb02 = NULL;
char thr_stack[SIGSTKSZ];

void print_element(TCB_t *element){
  printf("---------------------------------------------\n");
  printf("element->tid        = %d    \n",element->tid);
  printf("element->state      = %d    \n",element->state);
  printf("element->credCreate = %d    \n",element->credCreate);
  printf("element->credReal   = %d    \n",element->credReal);
  printf("element->context    = %p    \n",&element->context);
  printf("&element            = %p\n",element);
  printf("element->prev       = %p\n",element->prev);
  printf("element->next       = %p\n",element->next);
  printf("---------------------------------------------\n");
}

int picreate (int credCreate, void *(*start)(void*), void *arg){
  //printf("DBG - chamado picriate(). ID: %d\n", id);
  if (inicializada != 0) //Primeira chamada a funcao.
  {
    printf("DBG - Inicializando biblioteca - thread main.\n");
    tcb[id] = (TCB_t *) malloc(sizeof(TCB_t)); //Aloca TCB da main
    //*/Ajusta o TCB da main/*/
    tcb[id]->tid = 0;
    tcb[id]->state = 1; //Criada
    //TCBmain->context = context;
    tcb[id]->credCreate = 100;
    tcb[id]->credReal = 100;
    tcb[id]->next = NULL;
    tcb[id]->prev = NULL;
    //printf("Contexto da main construido.\n");
    //*/Ajusta o TCB da main/*/
    //getcontext(&context); //Salva o contexto da main
    //printf("Primeiro ID: %d\n", id);
    inicializada = 0;
    getcontext(&(tcb[id]->context)); //Salva o contexto da main
    //print_element(tcb[id]);
    //tcb[id]->context = context;
    printf("Contexto da main construido.\n");
  }

  printf("Criando nova thread. ");
  //printf("Executando picreate na biblioteca. Creditos: %d\n", credCreate);
  id = id+1;
  printf("Incrementado ID.\n");
  tcb[id] = (TCB_t *) malloc(sizeof(TCB_t)); //Aloca um novo TCB
  tcb[id]->tid = id;
  tcb[id]->state = 1;
  tcb[id]->credCreate = credCreate;
  tcb[id]->credReal = credCreate;
  //tcb[id]->context = context;
  tcb[(id-1)]->next = tcb[id];
  tcb[id]->prev = tcb[id-1];
  tcb[id]->next = NULL;
  //getcontext(&context); //Salva o contexto da main
  //getcontext(&(tcb[id]->context));
  //thrcontext.uc_link = NULL;
  thrcontext.uc_link = &context;
  thrcontext.uc_stack.ss_sp = thr_stack;
  thrcontext.uc_stack.ss_size = sizeof(thr_stack);
  //printf("argumento = 0x%08x\n",*(int*)arg);
  //makecontext(&(tcb[id]->context), (void (*)(void)) start, 1, arg);
  //tcb[id]->context = thrcontext;
  //swapcontext(&context, &thrcontext);
  //setcontext(&thrcontext);
  //TCBmain->context = context;
  //setcontext(&context);
  //void dispatcher();
  //printf("Saindo do create() com ID=%d\n", id);
  print_element(tcb[id]);
  return id;
}

int piyield(void){
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}

int piwait(int tid){
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  //printf("credReal %d\n", tcb[tid]->credReal);
  //swapcontext(&context, &(tcb[tid]->context));
  printf("tid: %d\n", tid);
  printf("%p\n", &(tcb[tid]->context));
  setcontext(&(tcb[tid]->context));
  return 0;
}

int pimutex_init(pimutex_t *mtx){
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}

int pilock (pimutex_t *mtx){
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}

int piunlock (pimutex_t *mtx){
  if (inicializada!=0) //Primeira chamada a funcao.
  {
    printf("Biblioteca nao inicializada.\n");
    return -1;
  }
  return -1;
}
