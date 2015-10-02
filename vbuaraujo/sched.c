#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#include "sched.h"

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

thread_t *so_make_thread() {
	thread_t *new = malloc(sizeof(thread_t));
	new->tid = so_next_tid++;
	new->numwaiters = 0;
	new->status = -42;
	new->context.uc_stack.ss_sp = NULL;
	new->context.uc_stack.ss_size = 0;
	getcontext(&new->context);
	return new;
}

void so_forgo_thread(thread_t *thread) {
	free_and_null(thread->context.uc_stack.ss_sp);
	if (thread->numwaiters == 0)
		free(thread);
}

int so_init() {
	thread_t *new = so_make_thread();
	new->next = new;
	so_current = new;
	so_previous = new;

	getcontext(&so_exit_context);
	so_exit_context.uc_stack.ss_sp = malloc(SO_EXIT_STACK_SIZE);
	so_exit_context.uc_stack.ss_size = SO_EXIT_STACK_SIZE;
	so_exit_context.uc_stack.ss_flags = 0;
	makecontext(&so_exit_context, so_exit, 1, 0);
	return 0;
}

int so_create(void (*proc)(), int arg) {
	thread_t *new = so_make_thread();
	new->context.uc_stack.ss_sp = malloc(SO_THREAD_STACK_SIZE);
	new->context.uc_stack.ss_size = SO_THREAD_STACK_SIZE;
	new->context.uc_stack.ss_flags = 0;
	new->context.uc_link = &so_exit_context;
	makecontext(&new->context, proc, 1, arg);
	new->next = so_current;
	so_previous->next = new;
	so_previous = new;

	return new->tid;
}

void so_yield() {
	if (so_previous == so_current) return;
	so_previous = so_current;
	so_current = so_current->next;
	// so_current->context.uc_link = &so_previous->context;
	swapcontext(&so_previous->context, &so_current->context);
}

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
	setcontext(&so_current->context);
}

thread_t *so_find_thread(int tid) {
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

int so_getid() {
	return so_current->tid;
}
