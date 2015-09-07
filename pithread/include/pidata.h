/*
 * pidata.h: arquivo de inclus�o de uso apenas na gera��o da libpithread
 *
 * Esse arquivo pode ser modificado. ENTRETANTO, deve ser utilizada a TCB fornecida.
 *
 */

 #include <ucontext.h>

#ifndef __pidata__
#define __pidata__

/* N�O ALTERAR ESSA struct */
typedef struct TCB {
	int	tid; 			// identificador da thread
	int	state;			// estado em que a thread se encontra
					// 0: Cria��o; 1: Apto; 2: Execu��o; 3: Bloqueado e 4: T�rmino
	int	credCreate;		// cr�ditos de cria��o da thread (atribu�dos na cria��o)
	int	credReal; 		// cr�ditos atuais da thread (usado para determinar a prioridade atual da thread)
	ucontext_t 	context;	// contexto de execu��o da thread (SP, PC, GPRs e recursos)
	struct TCB 	*prev; 		// ponteiro para o TCB anterior da lista
	struct TCB 	*next; 		// ponteiro para o pr�ximo TCB da lista
} TCB_t;

#endif
