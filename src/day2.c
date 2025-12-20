#include<stdio.h>
#include<math.h>
#include "lib/file.h"

void reverse(int *digits, size_t length) {
  for (size_t i = 0; i < length / 2; i++) {
    int tmp = digits[i];

    digits[i] = digits[length - 1 - i];
    digits[length - 1 - i] = tmp;
  }
}

int *split(long number, size_t *length) {
  int *digits = malloc(sizeof(int));
  size_t items = 0;
  
  while (number > 0) {
    int digit = number % 10;
    
    int *tmp = realloc(digits, (items + 1) * sizeof(int));
    if (!tmp) {
      free(digits);
      return NULL;
    }
    
    digits = tmp;
    digits[items++] = digit;

    number /= 10;
  }
  
  reverse(digits, items);
  *length = items;
  return digits;
}

void print_compare(const int *digits, size_t length, size_t chunk_len, size_t a, size_t b) {
  for (size_t i = 0; i < length; i++) {
    if (i == 0) {
      // printf("[");
    }
    if (i == a || i == b) {
      printf("\033[4m");
    }
    if (i == a && i == b) {
      printf("\033[31m");
    } else if (i == a) {
      printf("\033[33m");
    } else if (i == b) {
      printf("\033[32m");
    }
    printf("%i", digits[i]);
    if (i == a || i == b) {
      printf("\033[0m");
    }
    if (i == chunk_len - 1) {
      // printf("]");
    }
    printf(" ");
  }
  
  printf("\n");
}

int is_valid(const int *digits, size_t length) {
  size_t max_len = length / 2;
  
  // printf("digits (%zu): [", length);
  // for (size_t i = 0; i < length; i++) {
  //   printf("%i, ", digits[i]);
  // }
  // printf("]\n");
  
  // Step through valid sizes
  for (size_t i = 1; i <= max_len; i++) {
    if (length % i != 0) continue; // Invalid chunk size
    // printf("chunk_size=%zu\n", i);
    size_t chunks = (length / i) - 1;
    // printf("chunks=%zu\n", chunks);
    
    int valid = 1;
    for (size_t j = 0; j < chunks; j++) {
      // Assume w/ chunks is initially valid
      for (size_t k = 0; k < i; k++) {
        size_t index_a = k;
        size_t index_b = i + (j * i) + k;
        // printf("j=%zu, k=%zu, index_a=%zu, index_b=%zu\n", j, k, index_a, index_b);
        // print_compare(digits, length, i, index_a, index_b);
        if (digits[index_a] != digits[index_b]) {
          valid = 0;
          // printf("\033[31mINVALID\033[0m\n");
          break;
        }
      }
      if (valid == 0) break;
    }
    if (valid) return 1;
  } 
  
  return 0;
}

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day2.txt", &size);

  long result = 0;
  long part2 = 0;

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
        // Part1
        long len = log10(j) + 1;
        long p10 = pow(10, len / 2);
        long msb = j / p10;
        long top = msb * p10; 
        long bottom = j - top;
        if (msb == bottom) result += j; 
        
        // Part2
        size_t length = 0;
        int *digits = split(j, &length);
        if (!digits) {
          free(contents);
          return 1;
        }
        
        if (is_valid(digits, length)) {
          // printf("valid %zu: %li [", length, j);
          // for (size_t x = 0; x < length; x++) {
          //   printf("%i, ", digits[x]);
          // }
          // printf("]\n");
          part2 += j;
        }
        
        free(digits);
      }

      continue;
    }

    int parsed = c - '0';
    buffer = (buffer * 10) + parsed;
  }

  printf("Part 1: %li\n", result);
  printf("Part 2: %li\n", part2);

  free(contents);
  return 0;
}

