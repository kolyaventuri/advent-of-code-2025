#include<stdio.h>
#include<string.h>
#include "lib/file.h"

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day3.txt", &size);

  int part1 = 0;
  unsigned long part2 = 0;
  int batt_a = 0;
  int batt_b = 0;

  size_t BATT_SIZE = 12;
  int batt[BATT_SIZE];
  memset(batt, 0, BATT_SIZE);
  int p = 0;
  int m_index = -1;

  for (int i = 0; i < size; i++) {
    char c = contents[i];
    if (c == '\n') {
      part1 += 10*batt_a + batt_b;
      batt_a = 0;
      batt_b = 0;
      p = 0;
      m_index = -1;

      unsigned long acc = 0;
      for (size_t j = 0; j < BATT_SIZE; j++) {
        acc = (acc * 10) + batt[j];
      }
      part2 += acc;
      continue;
    }

    int parsed = c - '0';
    
    // Day 1
    int set_b = 1;
    if (parsed > batt_a && contents[i + 1] != '\n') { 
      batt_a = parsed;
      if (batt_a > batt_b) {
        batt_b = 0;
      }
      set_b = 0;
    }
    if (set_b && parsed > batt_b) {
      batt_b = parsed;
    }

    // Day2
    if (p < BATT_SIZE) {
      batt[p] = parsed;
      if (m_index > -1 && parsed < batt[m_index]) {
        m_index = p;
      } else if (m_index < 0) {
        m_index = p;
      }
    } else {
      int min = 10;
      int new_min = -1;
      for (int j = 0; j < BATT_SIZE; j++) {
        if (min >= batt[j]) {
          new_min = j;
          min = batt[j];
        } else if (batt[j] > min) {
          break;
        }
      }
      m_index = new_min;
      for (int j = m_index; j < BATT_SIZE - 1; j++) {
        int next = batt[j + 1];
        batt[j] = next;
      }
      if (batt[BATT_SIZE - 1] > parsed && m_index == BATT_SIZE - 1) continue;
      batt[BATT_SIZE - 1] = parsed;
    } 
    p++;
  }

  printf("Part1: %i\n", part1);
  printf("Part2: %lu\n", part2);

  free(contents);
  return 0;
}
