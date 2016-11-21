#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

char * get_line() {
  char * line = (char *) calloc(100, sizeof(char));
  fgets(line, sizeof(line) - 1, stdin);
  return line;
}

int main() {
   
}
