#include<stdio.h>
#include<math.h>
#include "lib/file.h"

__uint128_t ipow(long base, long exp) {
    if (exp < 0) return 0;
    __uint128_t result = 1;
    while (exp--) result *= base;
    return result;
}

long calc_nn(long n) {
  int exp = floor(log10(n)) + 1;
  return n * (ipow(10, exp) + 1);
}

unsigned long long repdigit( int n, int k) {
  if (k == 1) return 0;
  if (k < 2) return 0;
  long nn = calc_nn(n);
  __uint128_t a = ipow(nn - n, k) - ipow(n, k);
  __uint128_t b = (nn - 2 * n) * ipow(n, k - 2);

  __uint128_t result = a / b;

  return (unsigned long long) result;
}

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day2.test.txt", &size);

  long result = 0;
  unsigned long long result2 = 0;

  unsigned long long min = 0;
  unsigned long long max = 0;
  unsigned long long buffer = 0;

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

      printf("%llu, %llu\n", min, max);
      for (unsigned long long j = min; j <= max; j++) {
        long len = log10(j) + 1;
        long p10 = pow(10, len / 2);
        long msb = j / p10;
        long top = msb * p10; 
        long bottom = j - top;
        if (msb == bottom) {
          result += j; 
        }

        // printf("j: %llu, msb: %i, len: %i\n", j, msb, len);
        for (long k = 1; k < (len / 2); k++) {
          long p10_2 = pow(10, len - k);
          long msb_2 = j / p10_2;
          long len2 = log10(msb_2) + 1;

          long reps = len / len2;
          unsigned long long r = j < 10 ? j : repdigit(msb_2, reps);
          // printf(" k: %lu, p10_2: %lu, msb_2: %lu, len: %lu, len2: %lu\n", k, p10_2, msb_2, len, len2);
          // printf(" r: %llu, j: %llu, reps: %li\n", r, j, reps);
          if (r < 1) {
            printf("!! Something is deadfully wrong.\n");
            printf("r = %llu\n", r);
            printf("  k=%lu, p10_2=%lu", k, p10_2);
            printf("  j=%lu, msb_2=%li, len=%li, len2=%li, reps=%li\n", j, msb_2, len, len2, reps);
            printf("  repdigit(%llu, %lu)", msb_2, reps);
            return 1;
          }
          if (r == j) {
            // printf("  R> %llu [%li, %f]\n", r, msb_2, ((double)len / (double)len2));
            result2 += r; 
            break;
          }
        }
      }

      continue;
    }

    int parsed = c - '0';
    buffer = (buffer * 10) + (unsigned long long)parsed;
  }

  printf("Part 1: %li\n", result);
  printf("Part 2: %llu\n", result2);

  free(contents);
  return 0;
}

