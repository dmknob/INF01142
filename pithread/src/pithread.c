#include "../include/pithread.h"
#include "../include/pidata.h"
#include <stdio.h>

int picreate (int credCreate, void* (*start)(void*), void *arg)
{
  printf("Executando picreate na biblioteca. Creditos: %d\n", credCreate);
  return -1;
}
int piyield(void)
{
  return -1;
}
int piwait(int tid)
{
  return -1;
}
int pimutex_init(pimutex_t *mtx)
{
  return -1;
}
int pilock (pimutex_t *mtx)
{
  return -1;
}
int piunlock (pimutex_t *mtx)
{
  return -1;
}

/*int main(int argc, char const *argv[])
{
  printf("Executando a MAIN da biblioteca.\n");
  return 0;
}
*/
