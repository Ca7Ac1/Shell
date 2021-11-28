#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#include "parser.h"
#include "shell.h"
#include "command.h"

void shell() 
{
	while (1)
	{
		command* cmd = parse();
		command* orig = cmd;

		while (cmd)
		{
			char **tokens = cmd->tokens;

			if (strcmp(tokens[0], "cd") == 0)
			{
				chdir(tokens[1]);
			}
			else if (strcmp(tokens[0], "exit") == 0)
			{
				exit(0);
			}
			else
			{
				execute(tokens);
			}

			if (errno)
			{
				printf("%s", strerror(errno));
				cmd = NULL;
			}

			cmd = cmd->next;
		}

		freeCommands(orig);
	}
}

void execute(char **tokens)
{
	/*
	THIS WILL EVENTUALLY DEAL WITH PIPING AND REDIRECTION

	for(int j = 0; j < tokens[i].size; j++) 
	{
		if(strcmp(tokens[i][j], ">") == 0) {
			rrun1(tokens, j);	
		} else if(strcmp(tokens[i][j], "<") == 0) {
			rrun2(tokens, j);
		}
	}
	*/

	run(tokens);
}

void run(char **tokens)
{
	int c = fork();
	
	if(c)
	{
		int status;
		wait(&status);
	}
	else
	{
		execvp(tokens[0], tokens);
	}
}

/*
void rrun1(char **tokens, int r) {
	//split array
	char **first;
	int a = dup();
	dup2(STDOUT_FILENO, a);
	run(first);
	dup2(a, STDOUT_FILENO);	
}

void rrun2(char **tokens, int r) {
	//split array
	char **second;
	int a = dup();
	dup2(STDIN_FILENO, a);
	run(second);
	dup2(a, STDIN_FILENO);	
}
*/
