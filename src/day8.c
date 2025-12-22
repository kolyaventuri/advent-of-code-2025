#include<stdio.h>
#include<math.h>
#include "lib/file.h"

#define IS_TEST 1
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
    
    printf("Connect %zu to %zu\n", a, b);
    
    insert_edge(node_a, node_b);
  }
}

Graph **compress_edges(Graph *graph, size_t *num_graphs) {  
  Graph **collection = NULL; 
  size_t size = 0;
  
  for (size_t i = 0; i < graph->node_count; i++) {
    Node *node = &graph->nodes[i];

    if (node->visited) continue;
    node->visited = 1;
    if (node->edge_count == 0) continue;
    Graph *next = malloc(sizeof(Graph));
    next->nodes = NULL;
    next->node_count = 0;
    
    for (size_t j = 0; j < node->edge_count; j++) {
      Node *edge = node->edges[j];
      insert_node(next, edge->x, edge->y, edge->z);
    }
    
    Graph *tmp = realloc(collection, (size + 1) * sizeof(*collection));
    if (!tmp) {
      return NULL;
    } 
    collection = tmp;
    collection[size++] = next;
  }
  
  *num_graphs = size;
  
  return collection;
}

void reset_visited(Graph *graph) {
  for (size_t i = 0; i < graph->node_count; i++) {
    graph->nodes[i].visited = 0;
  }
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
  
  Pair *pairs = NULL; 
  get_pairs(graph, &pairs, TOTAL_PAIRS);

  for (size_t i = 0; i < TOTAL_PAIRS; i++) {
    Pair p = pairs[i];
    printf("Pair: %zu + %zu -> %f\n", p.a, p.b, p.dist);
  }
  
  part1_add_edges(graph, &pairs);
  for (size_t i = 0; i < graph->node_count; i++) {
    printf("Node %zu has %zu edges\n", i, graph->nodes[i].edge_count);
  }
  
  reset_visited(graph);
  size_t num_graphs = 0;
  Graph **graphs = compress_edges(graph, &num_graphs);
  printf("Generated %zu sub-graphs\n", num_graphs);
  for (size_t i = 0; i < num_graphs; i++) {
    Graph *g = graphs[i];
    printf("Graph %zu (size: %zu)\n", i, g->node_count);
    for (size_t j = 0; j < g->node_count; j++) {
      Node *n = &g->nodes[j];
      printf("  %i, %i, %i\n", n->x, n->y, n->z);
    }
  }
  
  printf("Part1: %i\n", part1);
  
  free(contents);
  free(temp_read);
  free_graph(graph);
  free(pairs);
  return 0;
}
