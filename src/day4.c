#include<stdio.h>
#include<string.h>
#include "lib/file.h"

void get_adjacent_cells(int *cells, char* contents, int grid_length, int index) {
  /*
  * a b c -> a b c ...
  * d X e -> d X e ...
  * f g h -> f g h ...
  */

  int offset = grid_length + 1;
  int a = index - offset - 1;
  int b = index - offset;
  int c = index - offset + 1;

  int d = index - 1;
  int e = index + 1;

  int f = index + offset - 1;
  int g = index + offset;
  int h = index + offset + 1;

  cells[0] = a;
  cells[1] = b;
  cells[2] = c;
  cells[3] = d;
  cells[4] = index;
  cells[5] = e;
  cells[6] = f;
  cells[7] = g;
  cells[8] = h;
}

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day4.txt", &size);

  int part1 = 0;
  int part2 = 0;

  size_t grid_length = 0;
  for (int i = 0; i < size; i++) {
    if (contents[i] == '\n') {
      if (grid_length == 0) grid_length = i;
    }
  }

  int removing = 1;
  int lock = 0;
  while (removing) {
    removing = 0;
    for (int i = 0; i < size; i++) {
      char c = contents[i];

      if (c == '@' || c == 'x') {
        int buf[9];
        get_adjacent_cells(buf, contents, grid_length, i);

        int count = 0;
        int count2 = 0;
        for (int j = 0; j < 9; j++) {
          if (buf[j] < 1 || buf[j] > size) continue;
          char b_c = contents[buf[j]];
          if (buf[j] == i) continue;
          if (b_c == '@' || b_c == 'x' || b_c == '*') count++;
          if (b_c == '@') count2++;
        }

        if (count < 4) {
          if (!lock) part1 += 1;
          contents[i] = 'x';
        }

        if (count2 < 4) {
          part2 += 1;
          contents[i] = '*';
          removing = 1;
        }
      }
    }

    lock = 1;
  }
 

  printf("Part1: %i\n", part1);
  printf("Part2: %i\n", part2);

  free(contents);
  return 0;
}
