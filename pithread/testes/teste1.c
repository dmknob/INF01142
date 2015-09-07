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
  int id0, id1;
  id0 = picreate(1, func0, (void *)&i);
  id1 = picreate(2, func0, (void *)&i);
  printf("ID0: %d\n", id0+1);
  //func0((void *)&i);
  return 0;
}
