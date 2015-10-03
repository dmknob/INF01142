#include "../include/listmanager.h"


TCB_t *aptos = NULL, *aptos_exp = NULL; //listas de aptos e aptos-expirados
TCB_t *bloqueados = NULL; //lista de bloqueados
TCB_t *exec = NULL; //'lista' da thread em execução
TCB_t *maintcb = NULL;
TCB_t *temp = NULL; //ponteiro temporario
ucontext_t context; //Armazena o contexto
//char stack[SIGSTKSZ]; //pilha para contextos
char stack[65536] = ""; //pilha para contextos
int id = 0; //controle de IDs de threads

void dispatcher(void)
{ //despachante
  printf("-Dispatcher:\n");

  //printf("Dispatcher      Troca context\n");
  //print_element(exec);
  //printf("Dispatcher      exec uclink: %p\n", exec->context.uc_link);
  //printf("Dispatcher      Contexto exec: %p\n", &exec->context);
  //context = exec->context;
  //printf("Dispatcher      uclink: %p\n", context.uc_link);
  //setcontext(&exec->context);
  //printf("main %p - exec %p\n", maintcb->context, exec->context);
  getcontext(&aptos->context);
  setcontext(&exec->context);
  //swapcontext(&maintcb->context, &exec->context);
  return;
}

void sched(void)
{ //escalonador
  printf("-Sched:\n");
  if (aptos == NULL){ //Acabou os aptos
    temp = aptos;
    aptos = aptos_exp;
    aptos_exp = temp;
/*    if (aptos == NULL){
      printf("Fudeu! Ngm apto a executar.\n");
      return -1;
    }
*/
  }
  //printf("Sched           Muda exec\n");
  exec = aptos; //'muda a thread em execução'
  //printf("Sched           Remove apto\n");
  aptos = remove_element(aptos, aptos);  //retira a thread que vai para execução da lista de aptos
  //print_element(maintcb);
  dispatcher();
}

int picreate (int credCreate, void* (*start)(void*), void *arg){
  if (id == 0){ //primeira thread(main), inicializando biblioteca.
    exec = insert_new(aptos, 100, id);
    maintcb = exec;
    //printf("main context: %p\n", maintcb->context);
    //printf("main context uclink: %p\n", maintcb->context.uc_link);
    getcontext(&maintcb->context);
  }

  id = id+1;
  printf("Picreate - incrementei ID para: %d\n", id);
  aptos = insert_new(aptos, credCreate, id);

  temp = find_tid(aptos, id); //ponteiro para o TCB dessa thread
  if (temp != NULL){
    //printf("DBG - salva contexto\n");
    getcontext(&context);
    context.uc_link = &(maintcb->context);
    //context.uc_stack.ss_sp = stack;
    context.uc_stack.ss_sp = malloc(sizeof(stack));
    context.uc_stack.ss_size = sizeof(stack);
    makecontext(&context, (void (*)(void)) start, 1, arg);
    temp->context = context;
    //print_element(temp);
    //printf("context: %p\n", &temp->context);
  }
  //printf("ID: %d\n", (find_tid(aptos, id))->tid);
  //(find_tid(aptos, id))->context = context;

  //getcontext(&context);
  //exec->context = context;
  //printf("exec context %p\n", exec->context.uc_link );
  return id;
}

int piyield(void){
  if (id == 0){ //nao inicializada
    return -1;
  }
  printf("-Piyield\n");
  //printf("Piyield          Ajusta creditos.\n");
  exec->credReal = (exec->credReal) - 10; //atualiza os creditos
  aptos = insert_element(aptos, exec);
  exec = NULL;
  sched();
  return 0;
}

int piwait(int tid){
  if (id == 0){ //nao inicializada
    return -1;
  }
  printf("-Piwait\n");
  /*printf("piwait com tid %d. ID=%d\n", tid, id);
  print_list(aptos);
  print_list(aptos_exp);
  print_list(exec);
  print_list(bloqueados);
  */
  /*if( (find_tid(aptos, tid) == NULL) && (find_tid(aptos_exp, tid) == NULL) ){  //
    printf("Fudeu!\n");
    return -1;  //Não foi possível executar wait com esse tid.
  }
  */

  //printf("piwait          Ajusta creditos.\n");
  exec->credReal = (exec->credReal) - 10; //atualiza os creditos
  exec->state = (-1) * tid;  //HACK, salva qual a thread que originou o bloqueio
  //printf("piwait          Bloqueia.\n");
  bloqueados = insert_element(bloqueados, exec);  //troca de executando pra bloqueado
  sched();
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
