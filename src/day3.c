#include<stdio.h>
#include<math.h>
#include "lib/file.h"

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day3.txt", &size);

  int part1 = 0;

  int batt_a = 0;
  int batt_b = 0;

  for (int i = 0; i < size; i++) {
    char c = contents[i];
    if (c == '\n') {
      part1 += 10*batt_a + batt_b;
      batt_a = 0;
      batt_b = 0;
      continue;
    }

    int parsed = c - '0';
    if (parsed > batt_a && contents[i + 1] != '\n') { 
      batt_a = parsed;
      if (batt_a > batt_b) {
        batt_b = 0;
      }
      continue;
    }

    if (parsed > batt_b) {
      batt_b = parsed;
    }
  }

  printf("Part1: %i\n", part1);

  free(contents);
  return 0;
}
