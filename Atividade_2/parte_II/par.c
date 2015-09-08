
/*
 * Compile com: gcc -o par par.c -Wall
 *
 * Execução: par
 */

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
 

void even(void) {
    int i;

     for (i =0; i <=10; i=i+2 )
         printf("%3d", i);

     return;

     /* O fluxo de execução, quando a função even terminar,seguira para o contexto
      * indicada por: "setcontext(&even_context->uc_link);", ou seja, a main, no
      * retorno da chamada "getcontext(&main_context) - linha 58" */ 
} 
 
int main(void)
{

    ucontext_t main_context, even_context;
    char even_stack[SIGSTKSZ];  /* Pilha para o contexto even */
    int ret_code;               /* Flag para identificar de onde, no código, getcontext retorna*/
 
    /* É necessário criar uma estrutura contexto a partir de um molde.
     * O contexto da propria main serve como esse molde. */

    getcontext(&even_context);

    /* Modifica-se o molde para criar o contexto para o novo fluxo de controle a ser criado.
     * Cada fluxo de controle recebe o contexto para onde ele deve ir quando terminar sua
     * execução (uc_link), uma pilha (ss_sp) e o tamanho da mesma. */

    even_context.uc_link          = &main_context;      /* contexto a executar no término */
    even_context.uc_stack.ss_sp   = even_stack;         /* endereço de início da pilha    */
    even_context.uc_stack.ss_size = sizeof(even_stack); /*tamanho da pilha */

    /* Define a função (even) a ser executada pelo novo fluxo de controle (even_context),
     * forcene a quantidade (0, no caso) e os eventuais parâmetros que cada fluxo 
     * recebe (nenhum). O typecast (void (*)(void)) é só para evitar warnings na
     * compilação e não afeta o comportamento da função */

    makecontext(&even_context, (void (*)(void)) even, 0); 

    /* salva o contexto da main em main_context. Quando a função "even" terminar,
     * o fluxo de controle será retomado a partir deste ponto (após getcontext)
     * devido ao fato do campo uc_link (linha 42) estar apontando para main_context */

    ret_code = 0;
    getcontext(&main_context);

    if ( ret_code == 0) {
       /* Testa a variável ret_code para diferenciar se a função getcontext anterior
        * (linha 58) retornou após sua primeira chamada simples, ou se ela está retornado
        *  via uc_link (se ret_code==1), que corresponde ao término de  even */

        ret_code = 1;             
        setcontext(&even_context);              /* posiciona o contexto para even */
        printf("NUNCA será executado!\n");
        return(-1);                             /* nunca será executado! */
    }
 
    printf("\n\n Terminando a main...\n");
    return 0;
}
