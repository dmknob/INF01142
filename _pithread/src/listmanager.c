
#define INIT_SIZE 1
#define MAX_PRIORITY 100

TCB_t *remove_element(TCB_t *first, TCB_t *deleted)
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
      if(first != NULL)
      {
	first->prev = NULL;
      }
    }
    deleted->next = NULL;
    deleted->prev = NULL;

    return first;
}

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
      if(first != NULL)
      {
	first->prev = NULL;
      }
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

    if(element == NULL)
    {
      new->prev = NULL;
      new->next = NULL;
      return new;
    }
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

TCB_t *find_tid(TCB_t *first, int tid)
{
  if(first != NULL)
  {
    do
    {
      if(first->tid == tid)
      {
	return first;
      }
      else
      {
	first=first->next;
      }
    }while (first->next != NULL);
  }
  return NULL;
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

TCB_t *insert_element(TCB_t *first, TCB_t *element)
{
  TCB_t *found;
  if(first != NULL)
  {
    found = find_element(first,element->credReal);
    if(found->credReal>=element->credReal)
    {
      element->prev = found;
      element->next = found->next;
      if (found->next != NULL)
      {
	found->next->prev = element;
      }
      found->next = element;
    }
    else
    {
      element->prev = NULL;
      element->next = found;
      found->prev = element;
      first = element;
    }
  }
  else
  {
    element->next = NULL;
    element->prev = NULL;
    first = element;
  }

  return first;
}


TCB_t *insert_new(TCB_t *first, int credCreate, int tid)
{
  TCB_t *found,*new;
  if(first != NULL)
  {
    found = find_element(first,credCreate);
  }
  else
  {
    found = NULL;
  }
  new = new_element(found,tid,credCreate);

  if((found == NULL)||((found == first)&&(credCreate > found->credCreate)))
  {
      first = new;
  }
  return first;
}

void print_element(TCB_t *element)
{
  printf("---------------------------------------------\n");
  printf("element->tid        = %d    \n",element->tid);
  printf("element->credCreate = %d    \n",element->credCreate);
  printf("&element            = 0x%08x\n",element);
  printf("element->prev       = 0x%08x\n",element->prev);
  printf("element->next       = 0x%08x\n",element->next);
}

void print_list(TCB_t *first)
{
  TCB_t *aux;
  printf("=============================================================================\n");
  if(first != NULL)
  {
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
}

/*
int main()
{
  TCB_t *first = NULL;
  TCB_t *wait = NULL;
  TCB_t *transf;
  int tid = 0;

  first = insert_new(first,100,tid++);
  first = insert_new(first,90,tid++);
  first = insert_new(first,80,tid++);
  first = insert_new(first,70,tid++);
  first = insert_new(first,90,tid++);
  //first = delete_element(first,find_tid(first,6));
  //wait = remove_element(first,find_tid(first,7));
  print_list(first);
  print_list(wait);

  transf = find_tid(first,4);
  first  = remove_element(first,transf);
  wait   = insert_element(wait,transf);

  transf = find_tid(first,1);
  first  = remove_element(first,transf);
  wait   = insert_element(wait,transf);

  print_list(first);
  print_list(wait);


  //print_list(wait);
  return(0);
}*/
