/*
 * Programa maior.c (tentativa 1)
 *
 * O processo filho procura o maior elemento de "vetor" que foi herdado do processo
 * pai e o processo pai imprime esse valor.
 *
 * Disclaimer: este programa, por ter fins didáticos, pode ter (ou não) erros 
 *             propositais em sua implementação. Descubra se é o caso!
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX 16
#define DONE 111

int vetor[MAX] = {12, 2, 6, 3, 43, 25, 10, 15, 8, 21, 34, 60, 1, 0, 16, 19};
int maior;

int main( ) {
    pid_t pid, child_pid;
    int   status, i;

    pid = fork ( );
    if ( pid == 0 ) {
       maior = vetor[0];
       for (i=0; i < MAX; i++)
           if ( vetor[i] > maior )
              maior = vetor[i];
       exit(DONE);
    }
    else{
       child_pid = wait(&status); 
       printf("Pai esperou o filho com PID = %d\n", child_pid);
       printf("\n*Maior elemento é %d.\n\n", maior);
       exit(0);
    }

}
