#include <stdio.h>
#include <stdlib.h>
#include "../include/pidata.h"

#define INIT_SIZE 5
#define MAX_PRIORITY 100 

TCB_t *delete_element(TCB_t *first, TCB_t *deleted)
{  
    if (deleted->next != NULL)
    {
      deleted->next->prev = deleted->prev;
    }
      
    if (deleted->prev!=NULL)
    {
      deleted->prev->next = deleted->next;
    }
    else
    {
      first = deleted->next;
      first->prev = NULL;
    }
    free(deleted);
    return first;
}

TCB_t *new_element(TCB_t *element, int new_tid, int new_credCreate)
{
    TCB_t *new;
    new = malloc(sizeof(TCB_t));
    new->tid = new_tid;
    new->credCreate = new_credCreate;
    new->credReal = new_credCreate;
    
    if(element->credCreate>=new_credCreate)
    {
      new->prev = element;
      new->next = element->next;
      if (element->next != NULL)
      {
	element->next->prev = new; 
      }
      element->next = new;
      
    }
    else
    {
      new->prev = NULL;
      new->next = element;
      element->prev = new;
    }
    return new;
}

TCB_t *find_element(TCB_t *first, int credReal)
{
  TCB_t *aux;
  do
  {
    aux = first;
    first = first->next;
  }while ((aux->next != NULL)&&(aux->next->credReal >= credReal));
  return aux;
}

TCB_t *move_element(TCB_t *first, TCB_t *element, int credReal)
{
  TCB_t *found;
  found = find_element(first,credReal);
  
  //desconnecting
  if(element->next != NULL)
  {
    element->next->prev = element->prev;
  }
  if (element->prev!=NULL)
  {
    element->prev->next = element->next;
  }
  else
  {
    first = element->next;
    first->prev = NULL;
  }
  
  //connecting
  if(credReal > found->credReal)
  {
    //início da fila
    found->prev = element;
    element->next = found;
    element->prev = NULL;
    first = element;
  }
  else
  {
    //meio da fila
    element->next = found->next;
    if(found->next!=NULL)
    {
      found->next->prev = element;
    }
    found->next = element;
    element->prev = found;
  }
  
  element->credReal = credReal;
  
  return first;
}

TCB_t *insert_element(TCB_t *first, int credCreate, int tid)
{
  TCB_t *found,*new;
  found = find_element(first,credCreate);
  new = new_element(found,tid,credCreate);
  
  if((found == first)&&(credCreate > found->credCreate))
  {
      first = new;
  }
  return first;
}

/*void print_element(TCB_t *element)
{
  printf("---------------------------------------------\n");
  printf("element->tid        = %d    \n",element->tid);
  printf("element->credCreate = %d    \n",element->credCreate);
  printf("&element            = 0x%08x\n",element);
  printf("element->prev       = 0x%08x\n",element->prev);
  printf("element->next       = 0x%08x\n",element->next);
}*/


void print_list(TCB_t *first)
{
  TCB_t *aux;
  do
  {
    aux=first;
    printf("---------------------------------------------\n");
    printf("list->tid        = %d    \n",first->tid);
    printf("list->credCreate = %d    \n",first->credCreate);
    printf("list->credReal   = %d    \n",first->credReal);
    //printf("&list          = 0x%08x\n",first);
    if(first->prev!=NULL)
    {
      printf("list->prev       = %d\n",first->prev->tid);//0x%08x\n",first->prev);
    }
    if(first->next!=NULL)
    {
      printf("list->next       = %d\n",first->next->tid);//0x%08x\n",first->next);
    }
    first=first->next;
  }while (aux->next != NULL);
}


int main()
{
  int tid;
  TCB_t *list;
  //TCB_t *credCreate[MAX_PRIORITY+1];
  
  list = malloc(INIT_SIZE * sizeof(TCB_t));
  
  for(tid=0;tid<INIT_SIZE;tid++)
  {
    list[tid].tid = tid;
    list[tid].credCreate = MAX_PRIORITY-tid*10;
    list[tid].credReal = list[tid].credCreate;
    if (tid == 0) 
    {
      list[tid].prev = NULL;
      list[tid].next = &list[tid+1];
    }
    else if (tid == INIT_SIZE - 1)
    {
      list[tid].prev = &list[tid-1];
      list[tid].next = NULL;
    }
    else
    {
      list[tid].prev = &list[tid-1];
      list[tid].next = &list[tid+1];
    } 
  }
   
  list = insert_element(list,102,tid++);
  list = insert_element(list,99,tid++);
  list = insert_element(list,99,tid++);
  list = insert_element(list,99,tid++);
  
  //list = delete_element(list,find_element(list,95));
  
  list = move_element(list,find_element(list,70),101);
  
  //insert_element(list,100,&tid);
  //insert_element(list,61,&tid);
  print_list(list);
  //getchar();
  //print_element(find_element(list,40));
  //printf("sizeof(list) = %d\n",sizeof(list));
  
  //free(list);
  //clean_list(list);
  return(0);
}

//OK-Pegar o tempo pelo programa
//OK-Mudar para calcular os n primeiros primos
//OK-Salvar os primos numa matrix, e depois exibi-los
//  -Comparar desempenho int contra float
//  -Otimizar...