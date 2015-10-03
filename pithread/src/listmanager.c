#include "../include/pidata.h"


TCB_t *new_element(TCB_t *element, int new_tid, int new_credCreate)
{ //Aloca e configura um novo TCB.
    TCB_t *new;
    new = malloc(sizeof(TCB_t));
    new->tid = new_tid;
    new->state = 1;
    new->credCreate = new_credCreate;
    new->credReal = new_credCreate;

    if(element == NULL){   //primeiro elemento, estava vazia
      new->prev = NULL;
      new->next = NULL;
      return new;
    }
    if(element->credCreate >= new_credCreate){ //meio ou fim
      new->prev = element;
      new->next = element->next;
      if (element->next != NULL){ //meio
	       element->next->prev = new;
      }
      element->next = new;
    }
    else{ //comeco da lista
      new->prev = NULL;
      new->next = element;
      element->prev = new;
    }
    return new;
}

TCB_t *remove_element(TCB_t *first, TCB_t *removed)
{ //remove elemento da lista (desencadeia)
    if (removed->next != NULL){
      removed->next->prev = removed->prev;
    }
    if (removed->prev!=NULL){
      removed->prev->next = removed->next;
    }
    else{
      first = removed->next;
      if(first != NULL){
        first->prev = NULL;
      }
    }
    removed->next = NULL;
    removed->prev = NULL;
    removed->next = NULL;
    removed->prev = NULL;
    return first;
}

TCB_t *delete_element(TCB_t *first, TCB_t *deleted){
    if (deleted->next != NULL){
      deleted->next->prev = deleted->prev;
    }
    if (deleted->prev!=NULL){
      deleted->prev->next = deleted->next;
    }
    else{
      first = deleted->next;
      if(first != NULL){
	       first->prev = NULL;
      }
    }
    free(deleted);
    return first;
}

TCB_t *find_element(TCB_t *first, int credReal)
{ //
  TCB_t *aux;
  do{
    aux = first;
    first = first->next;
  }while ((aux->next != NULL)&&(aux->next->credReal >= credReal));
  return aux;
}

TCB_t *find_tid(TCB_t *first, int tid)
{ //Retorna o ponteiro para thread com o id procurado, ou NULL
  if(first != NULL){ //lista nao vazia
    do{
      if(first->tid == tid){
        return first; //encontrado
      }
      else{
	       first=first->next;
      }
    }while (first->next != NULL);
  }
  return NULL; //nao encontrado
}

TCB_t *move_element(TCB_t *first, TCB_t *element, int credReal){
  TCB_t *found;
  found = find_element(first,credReal);

  //desconnecting
  if(element->next != NULL){
    element->next->prev = element->prev;
  }
  if (element->prev!=NULL){
    element->prev->next = element->next;
  }
  else{
    first = element->next;
    first->prev = NULL;
  }
  //connecting
  if(credReal > found->credReal){
    //início da fila
    found->prev = element;
    element->next = found;
    element->prev = NULL;
    first = element;
  }
  else{
    //meio da fila
    element->next = found->next;
    if(found->next!=NULL){
      found->next->prev = element;
    }
    found->next = element;
    element->prev = found;
  }
  element->credReal = credReal;
  return first;
}

TCB_t *insert_element(TCB_t *first, TCB_t *element){
  TCB_t *found;
  if(first != NULL){
    found = find_element(first,element->credReal);
    if(found->credReal>=element->credReal){
      element->prev = found;
      element->next = found->next;
      if (found->next != NULL){
        found->next->prev = element;
      }
      found->next = element;
    }
    else{
      element->prev = NULL;
      element->next = found;
      found->prev = element;
      first = element;
    }
  }
  else{
    element->next = NULL;
    element->prev = NULL;
    first = element;
  }
  return first;
}

TCB_t *insert_new(TCB_t *first, int credCreate, int tid)
{ //Insere novo elemento e retorna o começo da lista
  TCB_t *found,*new;
  if(first != NULL){
    found = find_element(first, credCreate);
  }
  else{
    found = NULL;
  }
  new = new_element(found, tid, credCreate);
  if( (found == NULL) || ( (found == first)&&(credCreate > found->credCreate) ) ){
    first = new;
  }
  return first;
}

void print_element(TCB_t *element){
  if(element != NULL){
    printf("---------------------------------------------\n");
    printf("element->tid        = %d    \n",element->tid);
    printf("element->state      = %d    \n",element->state);
    printf("element->credCreate = %d    \n",element->credCreate);
    printf("element->credReal   = %d    \n",element->credReal);
    printf("element->context    = %p    \n",&element->context);
    printf("&element            = %p\n",element);
    printf("element->prev       = %p\n",element->prev);
    printf("element->next       = %p\n",element->next);
    printf("---------------------------------------------\n");
  }
}

void print_list(TCB_t *first){
  TCB_t *aux;
  printf("=====%p========================================================================\n", first);
  if(first != NULL){
    do{
      aux=first;
      printf("---------------------------------------------\n");
      printf("list->tid        = %d    \n",first->tid);
      printf("list->state      = %d    \n",first->state);
      printf("list->credCreate = %d    \n",first->credCreate);
      printf("list->credReal   = %d    \n",first->credReal);
      printf("first->context   = %p    \n",&first->context);
      if(first->prev!=NULL){
        printf("list->prev       = %d\n",first->prev->tid);//0x%08x\n",first->prev);
      }
      if(first->next!=NULL){
        printf("list->next       = %d\n",first->next->tid);//0x%08x\n",first->next);
      }
      first=first->next;
    }while (aux->next != NULL);
  }
}
