#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#define free_and_null(p) ({ if (p) { free(p); p=NULL; } })
#define SO_THREAD_STACK_SIZE 65536
#define SO_EXIT_STACK_SIZE 16384

typedef struct thread_t {
	int tid;
	ucontext_t context;
	int numwaiters;
	int status;
	struct thread_t *next;
} thread_t;

thread_t *so_current, *so_previous;
int so_next_tid = 0;
ucontext_t so_exit_context;

void so_exit(int status) {
	if (so_previous == so_current) {
		printf("Last thread exited (status %d)!\n", status);
		exit(status);
	}

	thread_t *dead = so_current;
	so_current = so_current->next;
	so_previous->next = so_current;

	dead->status = status;
	dead->next = NULL;  // This is used to check for death in so_join.
	so_forgo_thread(dead);
	printf("->	set so_current->context: %p	<-\n", so_current->context);
	setcontext(&so_current->context);
}

thread_t *so_make_thread() {	//Cria uma thread main (malloc, getcontext)
	thread_t *new = malloc(sizeof(thread_t));
	new->tid = so_next_tid++;
	new->numwaiters = 0;
	new->status = -42;
	new->context.uc_stack.ss_sp = NULL;
	new->context.uc_stack.ss_size = 0;
	getcontext(&new->context);
	return new;
}

void so_forgo_thread(thread_t *thread) {	//Liberar memoria
	free_and_null(thread->context.uc_stack.ss_sp);
	if (thread->numwaiters == 0)
		free(thread);
}

int so_init() {
	thread_t *new = so_make_thread();	//Cria uma thread main (malloc, getcontext)
	new->next = new;	//'Encadeia' a main
	so_current = new;
	so_previous = new;

	getcontext(&so_exit_context);	//Aponta o contexto para o encerrador
	so_exit_context.uc_stack.ss_sp = malloc(SO_EXIT_STACK_SIZE);
	so_exit_context.uc_stack.ss_size = SO_EXIT_STACK_SIZE;
	so_exit_context.uc_stack.ss_flags = 0;
	makecontext(&so_exit_context, so_exit, 1, 0);	//
	return 0;
}

int so_create(void (*proc)(), int arg) {
	thread_t *new = so_make_thread();	//Cria uma thread(malloc, getcontext)
	new->context.uc_stack.ss_sp = malloc(SO_THREAD_STACK_SIZE);
	new->context.uc_stack.ss_size = SO_THREAD_STACK_SIZE;
	new->context.uc_stack.ss_flags = 0;
	new->context.uc_link = &so_exit_context;	//Contexto para executar ao termino
	makecontext(&new->context, proc, 1, arg);	//Funcao a executar quando chamada
	new->next = so_current;	//Encadeamento das threads
	so_previous->next = new;	//Encadeamento das threads
	so_previous = new;	//Encadeamento das threads
	return new->tid;
}

void so_yield() {
	if (so_previous == so_current) return;	//Só tem 1 thread, yield volta a executar thread unica.
	so_previous = so_current;
	so_current = so_current->next;
	// so_current->context.uc_link = &so_previous->context;
	printf("->	swap so_current->context: %p	<-\n", so_current->context);
	swapcontext(&so_previous->context, &so_current->context);
}


thread_t *so_find_thread(int tid) {	//Busca uma thread pelo ID, em uma lista circular
	thread_t *th = so_current;
	do {
		if (th->tid == tid)
			return th;
		th = th->next;
	} while (th != so_current);
	return NULL;
}

int so_join(int tid, int *status) {
	thread_t *waited = so_find_thread(tid);
	if (!waited) {
		printf("Attempted to join non-existent thread %d!\n", tid);
		return -1;
	}
	waited->numwaiters++;
	do so_yield(); while (waited->next);
	*status = waited->status;
	waited->numwaiters--;
	so_forgo_thread(waited);
	return 0;
}

int so_getid() {	//Retorna o ID da thread que chamou a função (a que esta executando).
	return so_current->tid;
}
