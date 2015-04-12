// McKenna Galvin
// catu.c
// CS 35L week 7

// use getchar and putchar to copy all of the bytes
// in standard input to standard output

#include <unistd.h>

int main() {
  char buf[1];
  while (read(0, buf, 1) > 0)
    write(1, buf, 1);
  return 0;
}
