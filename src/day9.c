#include<stdio.h>
#include "lib/file.h"

typedef struct point_t {
  int x, y;
} Point;

int pointInPoly(Point p, Point *verticies, size_t size) {
  int inside = 0;
  
  return inside;
}

int main(void) {
  size_t size = 0;
  char *contents = read_file("input/day9.test.txt", &size);
  
  Point *points = malloc(sizeof(Point));
  size_t items = 0;
  
  int acc = 0;
  int x = 0;
  for (size_t i = 0; i < size; i++) {
    char c = contents[i];
    if (c == ',') {
      x = acc;
      acc = 0;
      continue;
    }
    
    if (c == '\n') {
      Point point;
      point.x = x;
      point.y = acc;
      
      Point *tmp = realloc(points, (items + 1) * sizeof(Point));
      if (!tmp) {
        free(points);
        return 1;
      }
      
      points = tmp;
      points[items++] = point;

      acc = 0;
      x = 0;
      continue;
    }
    
    acc = (acc * 10) + (c - '0');
  }
  
  long max = 0;
  
  for (size_t i = 0; i < items; i++) {
    for (size_t j = 0; j < items; j++) {
      if (i == j) continue;
      
      Point a = points[i];
      Point b = points[j];
      
      long size_x = (b.x - a.x) + 1; 
      long size_y = (b.y  - a.y) + 1; 
      
      long tmp = size_x * size_y;
      if (tmp < 0) tmp *= - 1;
      
      if (tmp > max) max = tmp;
    }
  }
  
  printf("Part1: %lu\n", max);
  
  free(contents);
  free(points);
  return 0;
}
