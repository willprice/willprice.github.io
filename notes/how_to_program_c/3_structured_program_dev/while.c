#include <stdio.h>

main() {
  // This code doesn't work, I just wanted to test to see whether it was possible :(
  // This doesn't work because: while(<boolean expression>), assignments aren't 
  // boolean expressions.
  while(int t = 0; t<10) {
    printf("%d", t);
    t += 1;
  }
}
