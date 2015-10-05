#include "../include/listmanager.h"

#define THREAD_STACK_SIZE 65536

TCB_t *aptos = NULL, *aptos_exp = NULL; //listas de aptos e aptos-expirados
TCB_t *bloqueados = NULL; //lista de bloqueados
TCB_t *exec = NULL; //'lista' da thread em execução
TCB_t *maintcb = NULL;
TCB_t *temp = NULL; //ponteiro temporario
ucontext_t context; //Armazena o contexto
ucontext_t pi_exit_context;
//char stack[SIGSTKSZ]; //pilha para contextos
//char stack[65536] = ""; //pilha para contextos
int id = 0; //controle de IDs de threads

void dispatcher(void)
{ //despachante
  printf("-Dispatcher:\n");
  //swapcontext(&maintcb->context, &exec->context);
  printf("Exec TCB: ");
  print_element(exec);
  setcontext(&exec->context);
}

void sched(void)
{ //escalonador
  printf("-Sched:\n");
  if (aptos == NULL){ //Nenhum apto disponivel
    if (aptos_exp != NULL){ //Existem aptos expirados
      temp = aptos; //Inverte aptos com aptos_exp
      aptos = aptos_exp;
      aptos_exp = temp;
    }
    else {  //Nao tem mais nenhum apto..
      if (bloqueados == NULL){  //Nem bloqueado
        printf("Nada mais a executar!\n");
        pi_exit(0);  //Encerra OK
      }
      printf("Ngm apto, mas tem bloqueados..\n");
      pi_exit(-1);  //Encerra reclamando..
    }
  }
  exec = aptos;
  aptos = remove_element(aptos, exec);  //Remove exec da fila de aptos
  printf("Exec TCB: ");
  print_element(exec);
  dispatcher();
}

void pi_exit(int status)
{
  printf("--pi_exit - %d\n", status);
  //if (aptos != NULL)
  //{ //Tem mais thread pra executar
    //printf("Tem mais por executar.\n");
  sched();
  //}
  //printf("Trocando context.\n");
  //setcontext(&pi_exit_context);
  //setcontext(&exec->context);
}

void pi_init(void)
{ //Inicializa a biblioteca.
  maintcb = insert_new(maintcb, 100, id);
  printf("MainTCB: ");
  print_element(maintcb);
  exec = maintcb;
  printf("Exec TCB: ");
  print_element(exec);
  printf("Bloqueados TCB: ");
  print_element(bloqueados);
  //maintcb = aptos;
  //maintcb->next = NULL;
  //maintcb->prev = NULL;
  getcontext(&pi_exit_context); //inicializa um contexto
  pi_exit_context.uc_stack.ss_sp = malloc(THREAD_STACK_SIZE);
  pi_exit_context.uc_stack.ss_size = THREAD_STACK_SIZE;
  makecontext(&pi_exit_context, pi_exit, 1, 0);

  getcontext(&maintcb->context); //inicializa um contexto pra main
  maintcb->context.uc_stack.ss_sp = malloc(THREAD_STACK_SIZE);
  maintcb->context.uc_stack.ss_size = THREAD_STACK_SIZE;
  //makecontext(&pi_exit_context, pi_exit, 1, 0);
  //return 0;
}

int picreate (int credCreate, void* (*start)(void*), void *arg){
  TCB_t *new = NULL;
  if (id == 0){ //primeira thread(main), inicializando biblioteca.
    pi_init();
  }
  printf("-Picreate\n");
  id = id+1;
  aptos = insert_new(aptos, credCreate, id);   //Cria e encadeia
  new = find_tid(aptos, id);  //Localiza o que foi criado
  getcontext(&new->context); //inicializa um contexto pra main
  printf("getcontext dentro de picreate. ID: %d\n", id);
  new->context.uc_stack.ss_sp = malloc(THREAD_STACK_SIZE);
  new->context.uc_stack.ss_size = THREAD_STACK_SIZE;
	new->context.uc_stack.ss_flags = 0;
	new->context.uc_link = &pi_exit_context;	//Contexto para executar ao termino
	makecontext(&new->context, (void (*)(void)) start, 1, arg);	//Funcao a executar quando chamada
  return id;
}

int piyield(void){
  if (id == 0){ //nao inicializada
    return -1;
  }
  printf("-Piyield\n");
  exec->credReal = exec->credReal - 10;  //Ajusta creditos
  aptos = insert_element(aptos, exec);  //Reinsere na lista de aptos a thread que chamou piyield
  sched();
  /*
  //printf("Piyield          Ajusta creditos.\n");
  exec->credReal = (exec->credReal) - 10; //atualiza os creditos
  aptos = insert_element(aptos, exec);
  exec = NULL;
  sched();
  */
  return 0;
}

int piwait(int tid){
  if (id == 0){ //nao inicializada
    return -1;
  }
  printf("-Piwait\n");
  //print_list(exec);
  //print_list(aptos);
  exec->credReal = exec->credReal - 10;  //Ajusta creditos
  bloqueados = insert_element(bloqueados, exec);  //Bloquea a thread que chamou piwait

  printf("MainTCB: ");
  print_element(maintcb);
  printf("Exec TCB: ");
  print_element(exec);

  sched();
    //swapcontext(&exec->context, &aptos->context);
/*
  //print_list(aptos);
  //print_list(aptos_exp);
  if( (find_tid(aptos, tid) == NULL) && (find_tid(aptos_exp, tid) == NULL) ){  //
    printf("Fudeu!\n");
    return -1;  //Não foi possível executar wait com esse tid.
  }
  //find_tid(aptos, tid)
  //troca thread para lista de bloqueados
  temp = find_tid(aptos, id);
  aptos = remove_element(aptos, temp);
  bloqueados = insert_element(bloqueados, temp);
  printf("Diminuindo credReal da thread %d\n", temp->tid);
  temp->credReal = (temp->credReal) - 10;
  getcontext(&temp->context); //salva o contexto atual
  setcontext(&aptos->context);

  //printf("credReal %d\n", tcb[tid]->credReal);
  //swapcontext(&context, &(tcb[tid]->context));
  //printf("tid: %d\n", tid);
  //printf("%p\n", &(tcb[tid]->context));
  //setcontext(&(tcb[tid]->context));
*/
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
