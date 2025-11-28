#include<stdio.h>
#include "lib/file.h"

int main(void) {
  size_t size = 0;
  char *contents = read_file("../day1.test.txt", &size);
  if (!contents) {
    printf("Failed to read file\n");
    return 1;
  }

  printf("%s\n", contents);  

  free(contents);
  return 0;
}
