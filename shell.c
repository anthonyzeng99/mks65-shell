#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
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
//returns pointer to array of parsed commands
char ** parse_command(char * command) {
  char ** parsed_command = (char **) calloc(100, sizeof(char));

  int i = 0; 
  while (command) {
    parsed_command[i] = strsep(&command, " \n ");
    if (strncmp(&parsed_command[i][0], " ", 1) == 0) {
      parsed_command[i] = &parsed_command[i][1];
    }
    i++;
  }
  parsed_command[i] = NULL;

  return parsed_command;
}

//runs command without redirection
void run_command(char * command) {
  char ** parsed_command = parse_command(command);

    int pid = fork();
    int status;
    if (pid == 0) {
      execvp(parsed_command[0], parsed_command);
    } 
    wait(&status);

    free(parsed_command);
}

//runs command with < and > redirection
void redir_run_command(char * command, char direction) {
  char * cmd1 = strsep(&command, &direction);
  char * cmd2 = strsep(&command, &direction);

  int file;
  char ** cmd_arr;
  if (direction == '<') {
     file = open(cmd1, O_WRONLY | O_CREAT, 0644);
     cmd_arr = parse_command(cmd2);
  } else if (direction == '>') {
     file = open(cmd2, O_WRONLY | O_CREAT, 0644);
     cmd_arr = parse_command(cmd1);
  }

  dup2(STDOUT_FILENO, 5);
  dup2(file, STDOUT_FILENO);

  int pid = fork();
  int status;
  if (pid == 0) {
    execvp(cmd_arr[0], cmd_arr);
  }
  wait(&status);

  dup2(5, STDOUT_FILENO);
}

//runs command with | redirection
void pipe_run_command(char * command) {
  char * cmd0 = strsep(&command, "|");
  char * cmd1 = strsep(&command, "|");

  char ** cmd_arr0 = parse_command(cmd0);
  char ** cmd_arr1 = parse_command(cmd1);

  int pipe_num[2];
  pipe(pipe_num);
  
  int pid0 = fork();
  int status0;
  if (pid0 == 0) {
    dup2(STDOUT_FILENO, 5);
    dup2(pipe_num[1], STDOUT_FILENO);
    close(pipe_num[0]);
    close(pipe_num[1]);

    execvp(cmd_arr0[0], cmd_arr0);

  }

  int pid1 = fork();
  int status1;
  if (pid1 == 0) {
    dup2(STDIN_FILENO,6);
    dup2(pipe_num[0], STDIN_FILENO);
    close(pipe_num[1]);
    close(pipe_num[0]);

    execvp(cmd_arr1[0], cmd_arr1);
  }

  close(pipe_num[0]);
  close(pipe_num[1]);
  wait(&status0);
  wait(&status1);
  
}


int main() {
  char * line = get_line();  
  char ** commands = parse_line(line);

  int command_ctr = 0; 
  while (commands[command_ctr]) {
    char * command = commands[command_ctr];

    if (strchr(command, '<')) {

      redir_run_command(command, '<');

    } else if (strchr(command, '>')) {

      redir_run_command(command, '>');

    } else if (strchr(command, '|')) {

      pipe_run_command(command);

    } else {
      run_command(command);
    } 

    command_ctr++;

  }   
  free(line);
  free(commands);

}
