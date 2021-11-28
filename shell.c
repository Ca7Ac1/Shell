#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "parser.h"
#include "shell.h"
#include "command.h"

void shell() {
	while (true)
	{
		command* cmd = parse();
		
		while (cmd)
		{
			char **tokens = cmd->tokens;

			if (strcmp(tokens[0], "cd") == 0)
			{
				chdir(tokens[1]);
			}
			else if (strcmp(tokens[0], "exit" == 0))
			{
				exit(0);
			}
			else
			{
				execute(tokens);
			}

			if (errno)
			{
				cout << strerror(errno);
			}

			cmd = cmd->next;
		}

		freeCommands(cmd);
	}
}

void run(char **tokens)
{
	int c = fork();
	if(!c) {
		execvp(tokens[0], tokens);
	}
}

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

void command(char *cmd)
{
    format(cmd);
    int c = fork();
    
    if (!c)
    {
        execvp(cmd[0], cmd);
    }
}
