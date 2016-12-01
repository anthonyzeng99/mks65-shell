#ifndef SHELL_H
#define SHELL_H

#endif

char * get_line();

char ** parse_line(char * line);

char ** parse_command();

void run_command (char * command);

void redir_run_command(char * command, char direction);

void pipe_run_command(char * command);


