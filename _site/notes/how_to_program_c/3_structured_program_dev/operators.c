#include <stdio.h>

int a = 0;

main() {
  printf("a is: %d", a);
  printf("a is: %d", a++);
  ++a;
  printf("a is: %d", a);
}
