#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "shell.h"

/*======== char * get_line() ==========
	Inputs: 
	Returns: pointer to input

	takes in input from the terminal 
	====================*/
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

/*======== char ** parse_line() ==========
	Inputs:  char *line 
	Returns: pointer to array of commands

	divides the input into separate commands by ;
	====================*/
char ** parse_line(char * line) {
  int num_commands = 100; //Number of commands in the array;
  int num_chars = 100; //Number of characters in each command; 
  char ** commands = (char **) calloc(100, sizeof(char *)); //Allocates an ar
  
  //Parses and allocates memory for each command
  int i = 0;
  while (line) {
    commands[i] = (char*) calloc(num_chars, sizeof(char));
    commands[i] = strsep(&line,";");
    i++;
  }
    
  return commands;
}

/*======== char ** parse_command() ==========
	Inputs:  char *command
	Returns: pointer to array of parsed commands

	parses command by separating by spaces
	====================*/
char ** parse_command(char * command) {
  char ** parsed_command = (char **) calloc(100, sizeof(char));

  int i = 0; 
  while (command) {
    while (command[0] == ' ') command++;
    parsed_command[i] = strsep(&command, " ");
    i++;
  }
    parsed_command[i] = NULL;
  
  return parsed_command;
}

/*======== void run_command(() ==========
	Inputs:  char *command
	Returns:

	runs command without redirection or pipes
	====================*/
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

/*======== void redir_run_command() ==========
	Inputs:  char *command, char direction
	Returns: 

	runs command with <  and > redirection
	====================*/
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

/*======== void pipe_run_command() ==========
	Inputs:  char *command
	Returns: 

	runs command with | redirection
	====================*/
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
