#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

//takes in input from terminal
char * get_line() {
  char * line = (char *) calloc(100, sizeof(char));
  fgets(line, sizeof(line) - 1, stdin);
  return line;
}

//divides the input into separate commands and separate commands by spaces
char ** parse_line(char * line) {
  char ** commands = (char **) calloc(100, sizeof(char *));
  char *command[50]; 
  char *parsed_command[50];
  int i = 0;
  int j = 0;
  /*while (line) {
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
  return commands;*/

  if (strchr(line,'\n')){//replace newline 
    *strchr(line,'\n') = 0;
  }

  while (line){
    command[i] = strsep(&line,";");//one command
    while (command[i]){
      parsed_command[j] = strsep(&command[i]," ");//separates command by spaces
      j++;
    }
    //parsed_command[j] = NULL;
    commands[i] = *parsed_command;
    j = 0;
    i++;//go to next command
  }
  return commands;
}

//char * parse_command() {

//}

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
