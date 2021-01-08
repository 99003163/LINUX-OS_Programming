#include "func.h"
#include<stdio.h>

int main()
{
  int a, b, c, d;
  a = 2;
  b = 8;
  c = diff(a,b);
  d = cube(a);
  printf("c=%d,d=%d\n",c,d);
  return 0;
}
