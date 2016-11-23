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

char ** parse_line(char * line) {
  char ** commands = (char **) calloc(100, sizeof(char *));
  int i = 0;
  while (line) {
    char *command[50] = strsep(&line,";");
    char *parsed_command[50];
    int j = 0;
    while (command) {
      parsed_command[i] = strsep(&command," \n");
      j++;
    }
    parsed_command[j - 1] = NULL;
    i++;
  }
  //printf("%s\n", line);
  //printf("%d\n", i);
  return commands;
}

char * parse_command() {

}

int main() {
  char * line = get_line();
  char ** commands = parse_line(line);


  printf("0:%s\n", commands[0]);
  printf("1:%s\n", commands[1]);
  printf("2:%s\n", commands[2]);
  //  printf("%s\n", commands[2]);
  
  /*
  int i = 0;
  while (commands[i]) {
    printf("%s\n", commands[i]);
    i++;
  }
  */
}
