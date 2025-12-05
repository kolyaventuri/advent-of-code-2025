#include<stdio.h>
#include "lib/file.h"

typedef struct Interval { 
  unsigned long min;
  unsigned long max;

  struct Interval *next;
} Interval;

void free_list(Interval *head) {
  Interval *current = head;
  while (current != NULL) {
    Interval *next = current->next;
    free(current);
    current = next;
  }
}

void print_ranges(Interval *head) {
  Interval *current = head;
  printf("\n\nCurrent ranges:\n");
  while (current != NULL) {
    printf("[%lu, %lu] ", current->min, current->max);
    current = current->next;
  }
  printf("\n");
}

void merge_ranges(Interval *head) {
  Interval *current = head;

  while (current != NULL) {
    Interval *next = current->next;
    unsigned long next_min = next == NULL ? current->max + 1 : next->min;

    if (current->max >= next_min) {
      current->min = current->min < next->min ? current->min : next->min; 
      current->max = current->max > next->max ? current->max : next->max; 
      current->next = next->next;
      continue;
    }
    current = current->next;
  }
}

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day5.txt", &size);

  int part1 = 0;
  unsigned long part2 = 0;
  Interval *head = malloc(sizeof(Interval));
  head->min = 0;
  head->max = 0;
  head->next = NULL;

  Interval *current = head;

  Interval *next = malloc(sizeof(Interval));
  next->min = 0;
  next->max = 0;
  next->next = NULL;

  unsigned long acc = 0;
  int checking = 0; // 0 = ranges, 1 = ingredients;
  for (int i = 0; i < size; i++) {
    char c = contents[i];
    if (c == '\n' || c == '-') {
      if (acc == 0) {
        checking = 1;
        current = head; 
        merge_ranges(head);
        while (current != NULL) {
          // This is a stupid condition due to a bad LL implementation 
          if (current->max > 0) { 
            part2 += (current->max - current->min) + 1;
          }
          current = current->next;
        }
        current = head;
        continue;
      }

      // Validate in range
      if (checking) {
        while (current != NULL) {
          if (acc >= current->min && acc <= current->max) {
            part1 += 1;
            break;
          }
          current = current->next;
        }
        current = head;
        acc = 0;
        continue;
      }

      // Populate
      if (c == '-') {
        next->min = acc;
      } else {
        next->max = acc;

        // Insert into the list
        while (current != NULL) {
          // Fake an N+1 for the "next" value to imply end of list
          unsigned long next_min = current->next == NULL ? acc + 1 : current->next->min;
          if (next->min >= current->min && next->min <= next_min) {
            next->next = current->next;
            current->next = next;
            break;
          }
          current = current->next;
        }
        if (current->next != NULL) {
          current->next = next;
        }

        next = malloc(sizeof(Interval));
        next->min = 0;
        next->max = 0;
        next->next = NULL;

        // Seek back to head
        current = head;
      }

      acc = 0;
      continue;
    }

    int parsed = c - '0';
    acc = (acc * 10) + parsed; 
  }


  printf("Part1: %i\n", part1);
  printf("Part2: %lu\n", part2);

  free(next);
  free_list(head);
  free(contents);
  return 0;
}
