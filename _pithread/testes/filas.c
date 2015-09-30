#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <search.h>
#include "../include/pidata.h"

/*struct element
{
  struct element *forward;
  struct element *backward;
  char *name;
};*/

/*static struct element *
  new_element(void)
  {
    struct element *e;
    e = malloc(sizeof(struct element));
    if (e == NULL)
    {
      fprintf(stderr, "malloc() failed\n");
      exit(EXIT_FAILURE);
    }
    return e;
  }
*/


int main(int argc, char *argv[])
{
  int circular, opt, errfnd;
  TCB_t *prim = (TCB_t *) malloc(sizeof(TCB_t));
  TCB_t *seco = (TCB_t *) malloc(sizeof(TCB_t));
  TCB_t *thir = (TCB_t *) malloc(sizeof(TCB_t));

  prim->tid = 0;
  prim->state = 1;
  seco->tid = 1;
  seco->state=1;
  thir->tid = 2;
  thir->state = 1;

  //prim->prev = NULL;
  prim->next = seco;
  insque(prim, NULL);
  insque(seco, prim);
  insque(thir, seco);
  printf("%d\n", prim->next->tid);

  remque(prim);
  printf("%d\n", prim->next->tid);

  exit(EXIT_SUCCESS);
}
