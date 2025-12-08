#include<stdio.h>
#include<math.h>
#include "lib/file.h"

double euclidean_d3(int p1, int p2, int p3, int q1, int q2, int q3) {
  unsigned long a = powl(p1 - q1, 2); 
  unsigned long b = powl(p2 - q3, 2); 
  unsigned long c = powl(p2 - q3, 2); 
  
  unsigned long d = a + b + c;
  
  return sqrt(a + b + c);
}

typedef struct Node {
  int x, y, z;
  
  struct Node **edges;
  size_t edge_count;
} Node;

typedef struct Graph {
  Node *nodes;
  size_t node_count;
} Graph;

void insert_edge(Node *from, Node *to) {
  from->edges = realloc(from->edges, (from->edge_count + 1) * sizeof(Node*));
  from->edges[from->edge_count++] = to;
}

void free_graph(Graph *graph) {
  for (size_t i = 0; i < graph->node_count; i++) {
    free(graph->nodes[i].edges);
  }
  
  free(graph->nodes);
}

Node *insert_node(Graph *graph, int x, int y, int z) {
  graph->nodes = realloc(graph->nodes, (graph->node_count + 1) * sizeof(Node)); 
  
  Node *node = &graph->nodes[graph->node_count++];
  node->x = x;
  node->y = y;
  node->z = z;
  node->edges = NULL;
  node->edge_count = 0;
  
  return node;
}

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day8.test2.txt", &size);
  
  Graph *graph = malloc(sizeof(Graph));
  graph->nodes = NULL;
  graph->node_count = 0;
  
  int items = 0;
  int *temp_read = malloc(2 * sizeof(int));
  int temp_index = 0;
  unsigned int part1 = 1;
  
  int acc = 0;
  for (size_t i = 0; i < size; i++) {
    char c = contents[i];
    if (c == ',') {
      temp_read[temp_index] = acc;
      acc = 0;
      temp_index++;
      continue;
    }

    if (c == '\n') {
      int x = temp_read[0];
      int y = temp_read[1];
      int z = acc;
      insert_node(graph, x, y, z);

      acc = 0;
      temp_index = 0;
      continue;
    }
    
    int parsed = c - '0';
    acc = (acc * 10) + parsed;
  }
  
  for (size_t i = 0; i < graph->node_count; i++) {
    Node *node_a = &graph->nodes[i];
    double min_dist = MAXFLOAT;
    size_t min_j = graph->node_count + 1;

    for (size_t j = 0; j < graph->node_count; j++) {
      if (j == i) continue;
      Node *node_b = &graph->nodes[j];
      
      double dist = euclidean_d3(
        node_a->x,
        node_a->y,
        node_a->z,
        ///
        node_b->x,
        node_b->y,
        node_b->z
      );
      
      if (dist < min_dist) {
        min_dist = dist;
        min_j = j;
      }
    }
  }
  
  printf("Part1: %i\n", part1);
  
  free(contents);
  free(temp_read);
  free_graph(graph);
  return 0;
}
