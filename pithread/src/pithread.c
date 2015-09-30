#include "../include/listmanager.h"


TCB_t *aptos = NULL, *aptos_exp = NULL;
ucontext_t context; //Armazena o contexto
char stack[SIGSTKSZ];
int id = 0;

int picreate (int credCreate, void* (*start)(void*), void *arg){

  if (id == 0){ //main
    aptos = insert_new(aptos, 100, id);
    getcontext(&(aptos->context));
  }

  id = id+1;
  aptos = insert_new(aptos, credCreate, id);
  getcontext(&context);
  context.uc_link = &aptos->context;
  context.uc_stack.ss_sp = stack;
  context.uc_stack.ss_size = sizeof(stack);
  makecontext(&context, (void (*)(void)) start, 1, arg);
  printf("%p\n",find_tid(aptos, id));

  //(find_tid(aptos, id))->context = context;
  print_list(aptos);
  return id;
}

int piyield(void){
  if (id == 0){ //nao inicializada
    return -1;
  }
  return 0;
}

int piwait(int tid){
  if (id == 0){ //nao inicializada
    return -1;
  }
  //printf("credReal %d\n", tcb[tid]->credReal);
  //swapcontext(&context, &(tcb[tid]->context));
  //printf("tid: %d\n", tid);
  //printf("%p\n", &(tcb[tid]->context));
  //setcontext(&(tcb[tid]->context));
  return 0;
}

int pimutex_init(pimutex_t *mtx){
  if (id == 0){ //nao inicializada
    return -1;
  }
  return 0;
}

int pilock (pimutex_t *mtx){
  if (id == 0){ //nao inicializada
    return -1;
  }
  return 0;
}

int piunlock (pimutex_t *mtx){
  if (id == 0){ //nao inicializada
    return -1;
  }
  return 0;
}
