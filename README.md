# mks65-shell
by Anthony Zeng and Lucy Tang

**Features:**
* gets input and parses the commands
* executes commands
* executes commands with < and > redirection
* executes commands with | redirection
	

**Attempted:**


**Bugs:**


**Files & Function Headers:**
* shell.c
  * Handles all line parsing and executing functions
	
/*======== char * get_line() ==========
Inputs: 
Returns: pointer to input

takes in input from the terminal 
====================*/

/*======== char ** parse_line() ==========\s\s
Inputs:  char *line \s\s
Returns: pointer to array of commands\s\s

divides the input into separate commands by ;\s\s
====================*/\s\s

/*======== char ** parse_command() ==========\s\s
Inputs:  char *command\s\s
Returns: pointer to array of parsed commands\s\s

parses command by separating by spaces\s\s
====================*/\s\s
	
/*======== void run_command(() ==========\s\s
Inputs:  char *command\s\s
Returns:\s\s

runs command without redirection or pipes\s\s
====================*/\s\s
	
/*======== void redir_run_command() ==========\s\s
Inputs:  char *command, char direction\s\s
Returns: \s\s

runs command with <  and > redirection\s\s
====================*/\s\s
	
/*======== void pipe_run_command() ==========\s\s
Inputs:  char *command\s\s
Returns: \s\s

runs command with | redirection\s\s
====================*/\s\s

* shell.h
  * Contains the header functions for shell.c
	
