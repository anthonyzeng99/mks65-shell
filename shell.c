#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

//takes in input from terminal
char * get_line() {
  int num_chars = 100;
  char * line = (char *) calloc(num_chars, sizeof(char));
  fgets(line, num_chars, stdin);
 
  //removes newline 
  if (strchr(line,'\n')){
    *strchr(line,'\n') = 0;
  }
  
  return line;
}

//divides the input into separate commands and separate commands by spaces
char ** parse_line(char * line) {
  int num_commands = 100; //Number of commands in the array;
  int num_chars = 100; //Number of characters in each command; 
  char ** commands = (char **) calloc(100, sizeof(char *));
  
  //Allocates memory for each command
  int ctr = 0;
  for (; ctr <= num_commands; ctr++) {
    commands[ctr] = (char*) calloc(num_chars, sizeof(char));
  }
  
  int i = 0;
  while (line) {
    commands[i] = strsep(&line,";");
    i++;
  }
    
  return commands;
}

int main() {
  char * line = get_line();  
  char ** commands = parse_line(line);


  printf("0:%s\n", commands[0]);
  printf("1:%s\n", commands[1]);
  printf("2:%s\n", commands[2]);
    
  /*
  int i = 0;
  while (commands[i]) {
    printf("%s\n", commands[i]);
    i++;
  }
  */
}
