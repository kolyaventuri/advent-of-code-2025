#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "lib/file.h"

#define IS_TEST 0
#define path (IS_TEST ? "input/day8.test.txt" : "input/day8.txt")
#define TOTAL_PAIRS (IS_TEST ? 10 : 1000)

double euclidean_d3(int p1, int p2, int p3, int q1, int q2, int q3) {
  double a = (double)p1 - q1;
  double b = (double)p2 - q2;
  double c = (double)p3 - q3;
  
  return sqrt(a*a + b*b + c*c);
}

typedef struct Node {
  int x, y, z;
  
  struct Node **edges;
  size_t edge_count;
  unsigned char visited;
} Node;

typedef struct Graph {
  Node *nodes;
  size_t node_count;
} Graph;

typedef struct Pair {
  size_t a;
  size_t b;
  double dist;
} Pair;

void insert_edge(Node *from, Node *to) {
  from->edges = realloc(from->edges, (from->edge_count + 1) * sizeof(Node*));
  from->edges[from->edge_count++] = to;

  to->edges = realloc(to->edges, (to->edge_count + 1) * sizeof(Node*));
  to->edges[to->edge_count++] = from;
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

void free_pairs(Pair **pairs, size_t size) {
  for (size_t i = 0; i < size; i++) {
    free(pairs[i]);
  }
  
  free(pairs);
}

void insert_by_dist(Pair **pairs, Pair next, size_t *length, size_t max_count) {
  size_t k = *length; 
  
  // We haven't hit the max count yet, grow the array
  if (k < max_count) {
    Pair *tmp = realloc(*pairs, (*length + 1) * sizeof(**pairs));
    if (!tmp) {
      return;
    }
    *pairs = tmp;
    (*length)++;
  } else if (next.dist > (*pairs)[max_count - 1].dist) {
    // Array is full, but this pair doesn't fit
    return;
  }

  // Look backwards, locating where in the array it should live
  while (k > 0 && (*pairs)[k - 1].dist > next.dist) {
      // Shift up by 1 each time
      (*pairs)[k] = (*pairs)[k - 1];
      k--;
  }

  // Insert in place
  (*pairs)[k] = next;
}

void get_pairs(Graph *graph, Pair **pairs, size_t count) {
  size_t current_count = 0;

  for (size_t i = 0; i < graph->node_count; i++) {
    Node *a = &graph->nodes[i];
    for (size_t j = i; j < graph->node_count; j++) {
      if (j == i) continue;
      Node *b = &graph->nodes[j];
      
      double dist = euclidean_d3(
        a->x,
        a->y,
        a->z,
        ///
        b->x,
        b->y,
        b->z
      );
      Pair pair;
      pair.a = i;
      pair.b = j;
      pair.dist = dist;

      insert_by_dist(pairs, pair, &current_count, count);
    }
  }
}

void part1_add_edges(Graph *graph, Pair **pairs) {
  for (size_t i = 0; i < TOTAL_PAIRS; i++) {
    size_t a = (*pairs)[i].a;
    size_t b = (*pairs)[i].b;
    
    Node *node_a = &graph->nodes[a];
    Node *node_b = &graph->nodes[b];
    
    // printf("Connect %zu to %zu\n", a, b);
    
    insert_edge(node_a, node_b);
  }
}

int visit_nodes(Node *node) {
  if (node->visited) return 0;

  int count = 1;
  node->visited = 1;

  for (size_t i = 0; i < node->edge_count; i++) {
    count += visit_nodes(node->edges[i]);
  }

  return count;
}

void compress_edges(Graph *graph, int **count, size_t *num_graphs) {  
  size_t size = 0;
  
  for (size_t i = 0; i < graph->node_count; i++) {
    Node *node = &graph->nodes[i];
    int tmp_count = visit_nodes(node);
    if (tmp_count < 2) continue;
    // printf("Graph %i has size %i\n", i, tmp_count);
    
    int *tmp = realloc(*count, (size + 1) * sizeof(**count));
    if (!tmp) {
      return; 
    }
    
    *count = tmp;
    
    (*count)[size++] = tmp_count;
  }
  
  *num_graphs = size;
}

void reset_visited(Graph *graph) {
  for (size_t i = 0; i < graph->node_count; i++) {
    graph->nodes[i].visited = 0;
  }
}

int cmp(const void* one, const void* two) {
  int a = *(const int*)one; 
  int b = *(const int*)two;
  
  if (a < b) return 1;
  if (a > b) return -1;
  return 0;
}

int main(void) {
  size_t size = 0;
  char *contents = read_file(path, &size);
  
  Graph *graph = malloc(sizeof(Graph));
  graph->nodes = NULL;
  graph->node_count = 0;
  
  int items = 0;
  int *temp_read = malloc(2 * sizeof(int));
  int temp_index = 0;
  
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
  
  Pair *pairs = NULL; 
  get_pairs(graph, &pairs, TOTAL_PAIRS);
  part1_add_edges(graph, &pairs);
  reset_visited(graph);

  size_t num_graphs = 0;
  int *graphs = NULL;
  compress_edges(graph, &graphs, &num_graphs);

  unsigned int part1 = 1;
  qsort(graphs, num_graphs, sizeof(int), cmp);

  for (size_t i = 0; i < 3; i++) {
    part1 *= graphs[i];
  }

  printf("Part1: %i\n", part1);
  
  free(contents);
  free(temp_read);
  free_graph(graph);
  free(pairs);
  free(graphs);
  return 0;
}
