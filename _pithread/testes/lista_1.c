#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../include/pidata.h"

#define MAX_SIZE 10

/*
struct t_element{
  char name[10];
  unsigned int index;
  struct t_element *prev;
  struct t_element *next;
};*/

void new_element(TCB_t *element, int new_index)
{
    TCB_t *aux1,*aux2;
    aux1 = malloc(sizeof( TCB_t));
    aux1->credReal = new_index;

    aux1->prev = element;
    aux1->next = element->next;
    aux2 = element->next;
    aux2->prev = aux1;
    element->next = aux1;
}

void clean_list( TCB_t *first)
{
   TCB_t *aux;
  unsigned int count;
  count = 0;

  do
  {
    printf("count = %d\n",count);
    aux=first->next;
    free(first);
    count++;
    first=aux;
  }while (aux->next != NULL);
}

void print_list( TCB_t *first)
{
   TCB_t *aux;
  do
  {
    aux=first;
    printf("---------------------------------------------\n");
    printf("list.index = %d    \n",first->credReal);
    printf("&list      = 0x%08x\n",first);
    printf("list.prev  = 0x%08x\n",first->prev);
    printf("list.next  = 0x%08x\n",first->next);
    first=first->next;
  }while (aux->next != NULL);
}


int main()
{
  long n;
   int size;
   TCB_t *list;
   TCB_t *list2;

  size = MAX_SIZE;
  list = malloc(MAX_SIZE * sizeof( TCB_t));

  for(n=0;n<MAX_SIZE;n++)
  {
    list[n].credReal = n;
    if (n == 0)
    {
      list[n].prev = NULL;
      list[n].next = &list[n+1];
    }
    else if (n == 9)
    {
      list[n].prev = &list[n-1];
      list[n].next = NULL;
    }
    else
    {
      list[n].prev = &list[n-1];
      list[n].next = &list[n+1];
    }
  }

  print_list(list);

  printf("sizeof(list) = %d\n",sizeof(list));

  getchar();
  list2 = malloc(MAX_SIZE * sizeof( TCB_t));
  new_element(&list[5],77);

  print_list(list);
  printf("sizeof(list) = %d\n",sizeof(list));

  free(list);
  free(list2);
  //clean_list(list);
  return(0);
}

//OK-Pegar o tempo pelo programa
//OK-Mudar para calcular os n primeiros primos
//OK-Salvar os primos numa matrix, e depois exibi-los
//  -Comparar desempenho int contra float
//  -Otimizar...
