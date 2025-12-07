#include<stdio.h>
#include "lib/file.h"

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day7.test.txt", &size);
  
  int part1 = 0;
  int part2 = 0;
  int beams = 0;
  
  int cols = 0;
  for (size_t i = 0; i < size; i++) {
    if (contents[i] == '\n') {
      cols = i;
      break;
    } 
  }
  
  int row = 0;
  for (size_t i = 0; i < size; i++) {
    char c = contents[i];
    if (c == '\n') {
      row++;
      continue;
    }
    
    if (c == 'S') {
      contents[((row + 1) * cols) + i + 1] = '|';
    }

    int x = i - (row * cols); 
    char above = contents[(row - 1) * cols + x - 1];
    if (c == '^' && above == '|') {
      contents[(row + 1) * cols + x] = '|';
      contents[(row + 1) * cols + x + 2] = '|';
      
      part1 += 1;
    } else if (above == '|') {
      contents[i] = '|';
    }
  }
  
  for (size_t i = 0; i < size; i++) {
    printf("%c", contents[i]);
  }
  
  printf("Part1: %i\n", part1);
  
  return 0;
}
