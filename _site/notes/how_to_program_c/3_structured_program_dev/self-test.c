#include <stdio.h>

main() {
  int x, y;
  printf("Please enter an integer x: ");
  scanf("%d", &x);
  printf("\n");
  printf("Please enter an integer y: ");
  scanf("%d", &y);
  printf("\n");

  int pow = 1;


  while(y > 0) {
    pow *= x;
    y--;
  }

  printf("x to the power of y is: %d", pow);
}
