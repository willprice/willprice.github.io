#include <stdio.h>

main() {
  int x, y, z, result;

  printf("Hello, enter 3 integers please.\n");
  scanf("%d%d%d", &x, &y, &z);
  result = x*y*z;
  printf("The result of the product of the 3 numbers\n\
you entered is: %d",  result);

  return 0;
}
