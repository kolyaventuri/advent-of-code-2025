#include<stdio.h>
#include "lib/file.h"

int main (void) {
  size_t size = 0;
  char *contents = read_file("input/day6.txt", &size);
  unsigned long long part1 = 0;
  unsigned long long part2 = 0;

  int items = 0;
  int *data = malloc(0);
  if (!data) return 1;

  int cols = 0;
  int rows = 0;

  // Some horrible parsing into one long int array
  int acc = 0;
  int index = 0; // Later tracking
  int length = 0;
  int temp_length = 0;
  int acc_2 = 0;

  for (int i = 0; i < size; i++) {
    char c = contents[i];
    temp_length++;

    // End of a number or line
    if (c == ' ' || c == '\n') {
      if (c == '\n') {
        length = temp_length > length ? temp_length : length; 
        temp_length = 0;
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
        unsigned long temp_p1 = operand == 0 ? 0 : 1;
        unsigned long temp_p2 = temp_p1;

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
            temp_p1 += value;
          } else {
            temp_p1 *= value;
          } 
        } 

        // part2
        int index2 = i - 1;
        acc = 0;
        while (acc == 0) {
          for (int k = 0; k < rows; k++) {
            int v = contents[index2 - (length * (rows - k))];
            int parsed_v = v - '0';
            if (parsed_v < 0) continue; 
            acc_2 = (acc_2 * 10) + parsed_v; 
          }
          
          if (operand == 0 && acc_2 > 0) {
            temp_p2 += acc_2;
          } else if (acc_2 > 0) {
            temp_p2 *= acc_2;
          }
          
          acc_2 = 0;
          index2++;
          int p = contents[index2];
          acc = p == ' ' ? 0 : -1;
        }

        part1 += temp_p1;
        part2 += temp_p2;
        index++;
      }

      acc = 0;
      acc_2 = 0;
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
  printf("Part2: %llu\n", part2);

  free(contents);
  free(data);
  return 0;
}
