#include <stdio.h>
#include <stdlib.h>

#include "calculadora.h"
#define NARGS 4

int main(int argc, char *argv[]) {
    int resul;

    if (argc != NARGS) {
       printf ("Uso: calc [arg1] [op] [arg2], onde arg1 e arg são inteiros e op é +, -, x, / \n");
       exit(0);
    }

    switch (*argv[2]) {
    case '+': resul = add_i(atoi(argv[1]), atoi(argv[3]));
              break;
    case '-': resul = sub_i(atoi(argv[1]), atoi(argv[3]));
              break;
    case 'x': resul = mul_i(atoi(argv[1]), atoi(argv[3]));
              break;
    case '/': resul = div_i(atoi(argv[1]), atoi(argv[3]));
              break;       
    default:
         printf("Operação inválida!\n");
         printf ("Uso: calc [arg1] [op] [arg2], onde arg1 e arg são inteiros e op é +, -, x, / \n");
         exit(0);
    }
    
    printf("     = %d\n", resul);
    exit(0);
}
