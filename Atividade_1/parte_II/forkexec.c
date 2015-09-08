#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int main( ) {
    pid_t pid;
    int status = -1; 

    if ((pid = fork()) != 0) {
       printf("Processo pai esperando filho PID=%d\n", pid);
       wait(&status);
       printf("Filho terminou com o status: %d\n",WEXITSTATUS(status));
       exit(0);
    }
    else {
       printf("Processo filho executando...\n");
       execl("/bin/ls","ls", "-la", NULL);
       printf("Filho terminando a execução...\n");
    }
}

