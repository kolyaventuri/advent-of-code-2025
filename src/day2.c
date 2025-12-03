#include<stdio.h>
#include<math.h>
#include "lib/file.h"

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day2.txt", &size);

  long result = 0;

  long min = 0;
  long max = 0;
  long buffer = 0;

  for (int i = 0; i < size; i++) {
    char c = contents[i];

    if (c == '-') {
      min = buffer;
      buffer = 0;
      continue;
    }

    if (c == '\n' || c == ',') {
      max = buffer;
      buffer = 0;

      for (long j = min; j <= max; j++) {
        long len = log10(j) + 1;
        long p10 = pow(10, len / 2);
        long msb = j / p10;
        long top = msb * p10; 
        long bottom = j - top;
        if (msb == bottom) result += j; 
      }

      continue;
    }

    int parsed = c - '0';
    buffer = (buffer * 10) + parsed;
  }

  printf("Part 1: %li\n", result);

  free(contents);
  return 0;
}

