#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 5
#define MAX_PRIORITY 100 

struct t_element{
  char name[10];
  unsigned int index;
  unsigned int priority;
  struct t_element *prev;
  struct t_element *next;
};

struct t_element *delete_element(struct t_element *first, struct t_element *deleted)
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

struct t_element *new_element(struct t_element *element, unsigned int new_index, unsigned int new_priority)
{
    struct t_element *new;
    new = malloc(sizeof(struct t_element));
    new->index = new_index;
    new->priority = new_priority;
    
    if(element->priority>=new_priority)
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

struct t_element *find_element(struct t_element *first, unsigned int priority)
{
  struct t_element *aux;
  do
  {
    aux=first;
    first=first->next;
  }while ((aux->next != NULL)&&(aux->next->priority>=priority));
  return aux;
}

struct t_element *insert_element(struct t_element *first, unsigned int priority, unsigned int index)
{
  struct t_element *found,*new;
  found = find_element(first,priority);
  new = new_element(found,index,priority);
  
  if((found==first)&&(priority>found->priority))
  {
      first = new;
  }
  return first;
}

void print_element(struct t_element *element)
{
  printf("---------------------------------------------\n");
  printf("element->index    = %d    \n",element->index);
  printf("element->priority = %d    \n",element->priority);
  printf("&element          = 0x%08x\n",element);
  printf("element.prev      = 0x%08x\n",element->prev);
  printf("element.next      = 0x%08x\n",element->next);
}


void print_list(struct t_element *first)
{
  struct t_element *aux;
  do
  {
    aux=first;
    printf("---------------------------------------------\n");
    printf("list->index    = %d    \n",first->index);
    printf("list->priority = %d    \n",first->priority);
    //printf("&list          = 0x%08x\n",first);
    if(first->prev!=NULL)
    {
      printf("list->prev     = %d\n",first->prev->index);//0x%08x\n",first->prev);
    }
    if(first->next!=NULL)
    {
      printf("list->next     = %d\n",first->next->index);//0x%08x\n",first->next);
    }
    first=first->next;
  }while (aux->next != NULL);
}


int main()
{
  unsigned int index;
  struct t_element *list;
  //struct t_element *priority[MAX_PRIORITY+1];
  
  list = malloc(INIT_SIZE * sizeof(struct t_element));
  
  for(index=0;index<INIT_SIZE;index++)
  {
    list[index].index = index;
    list[index].priority = MAX_PRIORITY-index*10;
    if (index == 0) 
    {
      list[index].prev = NULL;
      list[index].next = &list[index+1];
    }
    else if (index == INIT_SIZE - 1)
    {
      list[index].prev = &list[index-1];
      list[index].next = NULL;
    }
    else
    {
      list[index].prev = &list[index-1];
      list[index].next = &list[index+1];
    } 
  }
   
  print_list(list);
     
  getchar();

  list=insert_element(list,101,index++);
  list=insert_element(list,99,index++);
  list=insert_element(list,99,index++);
  list=insert_element(list,99,index++);
  
  list=delete_element(list,find_element(list,101));
  
  //insert_element(list,100,&index);
  //insert_element(list,61,&index);
  print_list(list);
  
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