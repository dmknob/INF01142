#include "../include/pithread.h"
#include <stdio.h>


void* func0(void *arg)
{
  printf("\n--->Eu sou a thread ID1 em func0 imprimindo %d<---\n\n", *(int*)arg);
  return;
}

void* func1(void *arg)
{
  printf("\n--->Eu sou a thread ID2 em func1 imprimindo %d<---\n\n", *(int*)arg);
  return;
}
int main(int argc, char *argv[])
{
  int i = 144;
  int id0, id1;//, id2, id3, id4;
  //printf("Resultado piwait: %d\n", piwait(id0));
  //printf("&i = 0x%08x\n",&i);
  id0 = picreate(20, func0, (void *)&i);
  id1 = picreate(30, func1, (void *)&i);
  //i = piwait(id1);

  i = piwait(id0);
  //printf("ID1: %d ID2: %d\n", id0, id1);
  //printf("ID2: %d\n", picreate(4, func0, (void *)&i));
  //printf("ID3: %d\n", picreate(5, func0, (void *)&i));
  //printf("ID4: %d\n", picreate(6, func0, (void *)&i));
  //func0((void *)&i);
  return 0;
}
