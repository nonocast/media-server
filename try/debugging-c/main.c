#include <stdio.h>

int main(void) {
  printf("hello world\n");

  int x = 1;
  for (int i = 0; i < 10; ++i) {
    x = x * 2;
  }

  printf("x: %d\n", x);

  x = x + 1;

  printf("x: %d\n", x);

  return 0;
}