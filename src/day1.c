#include<stdio.h>
#include "lib/file.h"

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day1.txt", &size);

  int location = 50;
  int count = 0;
  int count2 = 0;

  int acc = 0;
  int exp = 0;
  int dir = 0;

  for (int i = 0; i < size; i++) {
    char c = contents[i];

    if (c == '\n') {
      int hundreds = (acc / 100) % 10;
      if (hundreds > 0) {
        acc -= hundreds * 100;
        count2 += hundreds;
      }

      int next = acc * dir;
      int passed_zero = 0;
      int previous = location;

      location += next;
      if (location > 99) {
        location -= 100;
        passed_zero = location != 0 && previous != 0;
        if (passed_zero) {
        }
      } else if (location < 0) {
        location += 100;
        passed_zero = previous != 0;
      }
      
      if (location == 0) {
        count += 1;
        if (!passed_zero) { passed_zero = 1; }
      }

      count2 += passed_zero;

      acc = 0;
      exp = 0;
      dir = 0;
      continue;
    }

    int parsed = (int)c - 48;
    if (parsed == 28) {
      dir = -1;
      continue;
    } else if (parsed == 34) {
      dir = 1;
      continue;
    }

    acc = (acc * (10 * exp)) + parsed;
    exp = 1;
  }

  printf("Part 1: %i\n", count);
  printf("Part 2: %i\n", count2);

  free(contents);
  return 0;
}
