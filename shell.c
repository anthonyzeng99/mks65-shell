#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

//takes in input from terminal
//returns pointer to input
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

//divides the input into separate commands
//returns pointer to array of commands
char ** parse_line(char * line) {
  int num_commands = 100; //Number of commands in the array;
  int num_chars = 100; //Number of characters in each command; 
  char ** commands = (char **) calloc(100, sizeof(char *)); //Allocates an ar
  
  //Parses and allocates memory for each command
  int command_ctr = 0;
  while (line) {
    commands[command_ctr] = (char*) calloc(num_chars, sizeof(char));
    commands[command_ctr] = strsep(&line,";");
    command_ctr++;
  }
    
  return commands;
}

//parses command
//returns parsed command
char * parse_command(char * command) {
  char * parsed_command = (char *) malloc(100);

  int i = 0; 
  while (i) {
    parsed_command[i] = strsep(&command, " \n ");
    i++;
  }
  parsed_command[i - 1] = NULL;

  return parsed_command;
}

int main() {
  char * line = get_line();  
  char ** commands = parse_line(line);

  /*
  int command_ctr = 0; 
  while (commands[command_ctr]) {
    char * parsed_command = parse_command(commands[command_ctr]);
    execvp(parsed_command[0], parsed_command);
    command_ctr++;
  }
  */

  printf("0:%s\n", commands[0]);
  printf("1:%s\n", commands[1]);
  printf("2:%s\n", commands[2]);
    
  
}
