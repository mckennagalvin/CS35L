// McKenna Galvin
// catb.c
// CS 35L week 7

// use getchar and putchar to copy all of the bytes
// in standard input to standard output

#include <stdio.h>

int main() {
  int c = getchar();
  while (c != EOF) {
    putchar(c);
    c = getchar();
  }
  return 0;
}
