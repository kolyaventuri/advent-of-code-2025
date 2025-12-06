#include<stdio.h>
#include "lib/file.h"

int main (void) {
  size_t size = 0;
  char *contents = read_file("input/day6.txt", &size);
  unsigned long long part1 = 0;

  int items = 0;
  int *data = malloc(items * sizeof(int));
  if (!data) return 1;

  int cols = 0;
  int rows = 0;

  // Some horrible parsing into one long int array
  int acc = 0;
  int index = 0; // Later tracking
  for (int i = 0; i < size; i++) {
    char c = contents[i];

    // End of a number or line
    if (c == ' ' || c == '\n') {
      if (c == '\n') {
        rows++;
      }

      if (acc == 0) continue;

      if (acc > 0) {
        int *tmp = realloc(data , (items + 1) * sizeof(int));
        if (!tmp) {
          free(data);
          return 2;
        }

        data = tmp;
        data[items++] = acc;
      } else {
        int count = items / rows;
        int operand = acc == -1 ? 0 : 1; // -1 = +, -2 = *
        unsigned long temp = operand == 0 ? 0 : 1;
        // printf("[");
        for (int j = 0; j < rows; j++) {
          int value = data[j * count + index];
          if (value == 0) {
            printf("!! access value was unexpectedly 0\n");
            printf("j=%i, count=%i, index=%i\n", j, count, index);
            printf("data[%i]=%i\n", j * count + index, value);
            return 1;
          }
          // printf("%i", value);
          // if (j < rows -1) printf(", ");
          if (operand == 0) {
            temp += value;
          } else {
            temp *= value;
          }
        } 
        // printf("],");
        part1 += temp;
        // printf("\n");
        index++;
      }

      acc = 0;
      continue;
    }
    
    if (c == '+') {
      acc = -1;
      cols++;
      continue;
    } else if (c == '*') {
      acc = -2;
      cols++;
      continue;
    }

    int parsed = c - '0';
    acc = (acc * 10) + parsed;
  }
  
  printf("Part1: %llu\n", part1);

  free(contents);
  free(data);
  return 0;
}
