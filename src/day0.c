#include<stdio.h>
#include<string.h>
#include "lib/file.h"

int compare(const void *a, const void *b) {
  return *(const int*)a - *(const int*)b;
}

/**
 * 2024's day 1, as a test bed before we get going
 */
int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day0.txt", &size);
  if (!contents) {
    printf("Failed to read file\n");
    return 1;
  }

  int lines = 0;
  for (int i = 0; i < size; i++) {
    if (contents[i] == '\n') {
      lines += 1;
    }
  }

  int side_a[lines];
  int side_b[lines];
  memset(side_a, 0, sizeof side_a);
  memset(side_b, 0, sizeof side_b);
  int *side = side_a;
  size_t index = 0;
  int exp = 0;

  int count[99999];
  memset(count, 0, sizeof count);

  for (int i = 0; i < size; i++) {
    if (contents[i] == '\n') {
      count[side[index]] += 1;
      side = side_a;
      index += 1;
      exp = 0;
      continue;
    } else if (contents[i] == ' ') {
      exp = 0;
      side = side_b;
      continue;
    }
    exp = 1;
    int parsed = (int)contents[i] - 48;
    side[index] = (side[index] * (10 * exp)) + parsed;
  }

  qsort(side_a, sizeof(side_a) / sizeof(*side_a), sizeof(int), compare);
  qsort(side_b, sizeof(side_b) / sizeof(*side_b), sizeof(int), compare);

  printf("\n\n");
  int result = 0;
  for (int i = 0; i < lines; i++) {
    result += abs(side_a[i] - side_b[i]);
  }

  free(contents);

  printf("Part 1: %i\n", result);
  
  /** PART 2 */
  int result_2 = 0;
  for (int i = 0; i < lines; i++) {
    result_2 += side_a[i] * count[side_a[i]];
  }

  printf("Part 2: %i\n", result_2);
  return 0;
}
