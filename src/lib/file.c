#include<stdio.h>
#include<stdlib.h>

char *read_file(const char *path, size_t *out_size) {
  FILE *file = fopen(path, "r");
  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(size + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, size, file);
  fclose(file);
  
  if (out_size) {
    *out_size = size;
  }

  return buffer;
}
