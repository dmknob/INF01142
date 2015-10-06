#include "../include/listmanager.h"

#define THREAD_STACK_SIZE 65536

TCB_t *aptos = NULL, *aptos_exp = NULL; //listas de aptos e aptos-expirados
TCB_t *bloqueados = NULL; //lista de bloqueados
TCB_t *exec = NULL; //'lista' da thread em execução
TCB_t *maintcb = NULL;
ucontext_t pi_exit_context;
int id = 0; //controle de IDs de threads

void dispatcher(void)
{
  //printf("-Dispatcher:\n");
  exec->state = 2;
  setcontext(&exec->context);
  //swapcontext(&maintcb->context, &exec->context);
  //swapcontext(&pi_exit_context, &exec->context);
}

void sched(void)
{
  TCB_t *temp = NULL; //ponteiro temporario
  printf("-Sched:\n");
  if (aptos == NULL){ //Nenhum apto disponivel
    printf("Aptos == NULL.\n");
    if (aptos_exp != NULL){ //Existem aptos expirados
      printf("Aptos_exp != NULL.\n");
      temp = aptos; //Inverte aptos com aptos_exp
      aptos = aptos_exp;
      aptos_exp = temp;
    }
    else {  //Nao tem mais nenhum apto..
      printf("Aptos_exp == NULL.\n");
      if (bloqueados == NULL){  //Nem bloqueado
        printf("Bloqueados == NULL!\n");
        printf("Encerrando.\n");
        exit(-1);
        //pi_exit(0);  //Encerra OK
      }
      printf("Ngm apto, mas tem bloqueados..\n");
      printf("Desbloqueando:\n");
      temp = bloqueados;  //Pega o primeiro bloqueado
      if(temp->credReal <= 80){
        temp->credReal = temp->credReal + 20;  //Ajusta creditos
      }
      else{
        temp->credReal = 100;  //Ajusta creditos
      }
      temp->state = 1;  //Apto novamente
      bloqueados = remove_element(bloqueados, temp);
      aptos = insert_element(aptos, temp);  //Insere como apto
    }
  }
  if(aptos->state == 1){  //Realmente apto
    exec = aptos; //Pega o proximo TCB a executar
    aptos = remove_element(aptos, exec);  //Remove ele da fila de aptos
    //printf("Exec TCB: ");
    //print_element(exec);
    dispatcher();
  }
  else{
    printf("ERRO FATAL! TENTOU EXEC EM NAO APTO!\n");
    exit (-1);
  }
}

void pi_exit(int status)
{
  printf("--pi_exit - %d\n", status);
  exec->state = 4;
  exec = delete_element(exec, exec);
  sched();
  //setcontext(&exec->context);
}

void pi_init(void)
{ //Inicializa a biblioteca.
  maintcb = insert_new(maintcb, 100, id);
  exec = maintcb;
  getcontext(&pi_exit_context); //inicializa um contexto
  pi_exit_context.uc_stack.ss_sp = malloc(THREAD_STACK_SIZE);
  pi_exit_context.uc_stack.ss_size = THREAD_STACK_SIZE;
  makecontext(&pi_exit_context, pi_exit, 1, 0);
  getcontext(&maintcb->context); //inicializa um contexto pra main
  maintcb->context.uc_stack.ss_sp = malloc(THREAD_STACK_SIZE);
  maintcb->context.uc_stack.ss_size = THREAD_STACK_SIZE;
}

int picreate (int credCreate, void* (*start)(void*), void *arg){
  TCB_t *new = NULL;
  if (id == 0){ //primeira thread(main), inicializando biblioteca.
    pi_init();
  }
  //printf("-Picreate\n");
  id = id+1;
  aptos = insert_new(aptos, credCreate, id);   //Cria e encadeia
  new = find_tid(aptos, id);  //Localiza o que foi criado
  new->state = 1;
  getcontext(&new->context); //inicializa um contexto
  new->context.uc_stack.ss_sp = malloc(THREAD_STACK_SIZE);
  new->context.uc_stack.ss_size = THREAD_STACK_SIZE;
	new->context.uc_stack.ss_flags = 0;
	new->context.uc_link = &pi_exit_context;	//Contexto para executar ao termino
	makecontext(&new->context, (void (*)(void)) start, 1, arg);	//Funcao a executar quando chamada
  return id;
}

int piyield(void){
  if (id == 0){ //nao inicializada
    return -2;
  }
  printf("-Piyield\n");
  exec->credReal = exec->credReal - 10;  //Ajusta creditos
  exec->state = 1;
  if(exec->credReal <= 0){ //Expirada
    exec->credReal = exec->credCreate;   //Restaura os creditos
    aptos_exp = insert_element(aptos_exp, exec);  //Insere na lista de aptos expirados
  }
  else{
    aptos = insert_element(aptos, exec);  //Reinsere na lista de aptos
  }
  sched();
  printf("----PiYield antes do return, após sched()\n");
  return 0;
}

int piwait(int tid){
  if (id == 0){ //nao inicializada
    return -2;
  }
  printf("-Piwait\n");
  exec->credReal = exec->credReal - 10;  //Ajusta creditos
  exec->state = 3;  //bloqueado
  if(exec->credReal < 0){ //Expirada
    exec->credReal = exec->credCreate;  //Restaura os creditos de criacao.
  }
  bloqueados = insert_element(bloqueados, exec);  //Bloquea a thread que chamou piwait
  sched();
  printf("----PiWait antes do return, após sched(). ID=%d\n", tid);
  return 0;
}

int pimutex_init(pimutex_t *mtx){
  if (id == 0){ //nao inicializada
    return -2;
  }
  return -1;
}

int pilock (pimutex_t *mtx){
  if (id == 0){ //nao inicializada
    return -2;
  }
  return -1;
}

int piunlock (pimutex_t *mtx){
  if (id == 0){ //nao inicializada
    return -2;
  }
  return -1;
}
