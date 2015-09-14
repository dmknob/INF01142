#include "../include/pithread.h"
#include <stdio.h>


void* func0(void *arg)
{
  printf("Eu sou a thread ID0 em func0 imprimindo %d\n", *((int *)arg));
  return;
}

int main(int argc, char *argv[])
{
  int i;
  int id0, id1;//, id2, id3, id4;
  //printf("Resultado piwait: %d\n", piwait(id0));
  id0 = picreate(2, func0, (void *)&i);
  id1 = picreate(3, func0, (void *)&i);
  printf("ID0: %d ID1: %d\n", id0, id1);
  printf("ID2: %d\n", picreate(4, func0, (void *)&i));
  printf("ID3: %d\n", picreate(5, func0, (void *)&i));
  //printf("ID4: %d\n", picreate(6, func0, (void *)&i));
  //func0((void *)&i);
  return 0;
}
