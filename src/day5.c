#include<stdio.h>
#include "lib/file.h"

typedef struct Node { 
  unsigned long min;
  unsigned long max;

  struct Node *prev;
  struct Node *next;
} Node;

void free_list(Node *head) {
  Node *current = head;
  while (current != NULL) {
    Node *next = current->next;
    free(current);
    current = next;
  }
}

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day5.txt", &size);

  int part1 = 0;
  Node *head = malloc(sizeof(Node));
  head->min = 0;
  head->max = 0;
  head->prev = NULL;
  head->next = NULL;

  Node *current = head;

  unsigned long acc = 0;
  int checking = 0; // 0 = ranges, 1 = ingredients;
  for (int i = 0; i < size; i++) {
    char c = contents[i];
    if (c == '\n' || c == '-') {
      if (acc == 0) {
        checking = 1;
        current = head;
        continue;
      }

      // Validate in range
      if (checking) {
        while (current->next != NULL) {
          if (acc >= current->min && acc <= current->max) {
            part1 += 1;
            printf("Found %lu in range [%lu, %lu]\n", acc, current->min, current->max);
            break;
          }
          current = current->next;
        }
        current = head;
        acc = 0;
        continue;
      }

      if (c == '-') {
        current->min = acc;
      } else {
        current->max = acc;
        Node *next = malloc(sizeof(Node));
        next->min = 0;
        next->max = 0;

        current->next = next;
        next->prev = current;
        printf("From: %lu to %lu\n", current->min, current->max);

        current = next;
      }

      acc = 0;
      continue;
    }

    int parsed = c - '0';
    acc = (acc * 10) + parsed; 
  }


  printf("Part1: %i\n", part1);

  free_list(head);
  free(contents);
  return 0;
}
