#include<stdio.h>
#include "lib/file.h"

typedef struct Node {
  struct Node *left;
  struct Node *center;
  struct Node *right;
  int explored;
  int paths;
  int is_splitter;
} Node;

void free_nodes(Node *head) {
  if (!head) return;

  if (head->left) {
    free_nodes(head->left);
  }
  if (head->right) {
    free_nodes(head->right);
  }
  
  if(head->center) {
    free_nodes(head->center);
  }
  
  free(head);
}

void free_map(Node **map, size_t size) {
  for (size_t i = 0; i < size; i++) {
    free(map[i]);
  }
  
  free(map);
}

// Get a free node from the map
Node *get_node(Node **map, size_t cols, size_t row, size_t col) {
  size_t id =  row * cols + col;

  if (!map[id]) {
    map[id] = malloc(sizeof *map[id]);
    *map[id] = (Node){0};
  }
  return map[id];
}

void clear_explored(Node **map, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (map[i]) map[i]->explored = 0;
  }
}

void traverse(char *contents, size_t size, size_t index, Node **map, size_t cols, Node *head) {
  if (!head) return;
  if (head->explored) return;
  head->explored = 1;
  size_t width = cols + 1;
  
  size_t rows = size / width;
  size_t row = index / width;
  size_t col = index % width;

  if (row + 1 >= rows) return;
  if (col == 0 || col + 1 >= cols) return;
  
  size_t down_center = (row + 1) * width + col;
  size_t down_left = down_center - 1; 
  size_t down_right = down_center + 1;
  
  
  char c_l = contents[down_left];
  char c_r = contents[down_right];
  char c_c = contents[down_center];
  
  if (c_c == '^') {
    Node *l_next = get_node(map, cols, row + 1, col - 1);
    head->left = l_next;
    Node *r_next = get_node(map, cols, row + 1, col + 1);
    head->right = r_next;
    head->is_splitter = 1;
    head->paths = -1;
    traverse(contents, size, down_left, map, cols, l_next);
    traverse(contents, size, down_right, map, cols, r_next);
    contents[down_left] = '|';
    contents[down_right] = '|';
    return;
  } else {
    Node *c_next = get_node(map, cols, row + 1, col);
    head->center = c_next;
    head->is_splitter = 0;
    head->paths = -1;
    traverse(contents, size, down_center, map, cols, c_next);
    contents[down_center] = '|';
  }
}

int walk_part1(Node *head) {
  if (!head) return 0;
  if (head->explored) return 0;
  head->explored = 1;
  int count = head->is_splitter ? 1 : 0;
  
  count += walk_part1(head->left);
  count += walk_part1(head->center);
  count += walk_part1(head->right);
  
  return count;
}

unsigned long walk_part2(Node *head) {
  if (!head) return 0;
  if (head->left == NULL && head->right == NULL && head->center == NULL) return 1;
  
  if (head->paths != -1) return head->paths;
  
  unsigned long count = 0;
  count += walk_part2(head->left);
  count += walk_part2(head->right);
  count += walk_part2(head->center);
  
  head->paths = count;
  
  return count;
}

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day7.txt", &size);
  
  int cols = 0;
  for (size_t i = 0; i < size; i++) {
    if (contents[i] == '\n') {
      cols = i;
      break;
    } 
  }
  
  size_t rows = size / (cols + 1);
  
  size_t head_index = 0;
  for (size_t i = 0; i < size; i++) {
    if (contents[i] == 'S') {
      head_index = i;
      break;
    }
  }

  Node **map = calloc(rows * cols, sizeof(Node*));
  size_t width = cols + 1;
  Node *head = get_node(map, cols, 0, head_index % width);
  
  traverse(contents, size, head_index, map, cols, head);
  clear_explored(map, size);
  
  int part1 = walk_part1(head);
  unsigned long part2 = walk_part2(head);
  
  // for (size_t i = 0; i < size; i++) {
  //   printf("%c", contents[i]);
  // }
  
  printf("Part1: %i\n", part1);
  printf("Part1: %lu\n", part2);
  
  free(contents);
  free_map(map, rows * cols);
  return 0;
}
