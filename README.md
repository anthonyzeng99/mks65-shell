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
	
  * char * get_line() 
    * Inputs: 
    * Returns: pointer to input
    * takes in input from the terminal 

  * char ** parse_line() 
    * Inputs:  char *line 
    * Returns: pointer to array of commands
    * divides the input into separate commands by ;

  * char ** parse_command()
    * Inputs:  char *command
    * Returns: pointer to array of parsed commands
    * parses command by separating by spaces
	
  * void run_command()
    * Inputs:  char *command
    * Returns:
    * runs command without redirection or pipes
 
  * void redir_run_command() 
    * Inputs:  char *command, char direction
    * Returns: 
    * runs command with <  and > redirection
	
  * void pipe_run_command() 
    * Inputs:  char *command
    * Returns: 
    * runs command with | redirection

* shell.h
  * Contains the header functions for shell.c
	
