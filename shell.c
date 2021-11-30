#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

#include "parser.h"
#include "shell.h"
#include "command.h"

void shell()
{
	char path[1000000];

	while (1)
	{
		getcwd(path, sizeof(path) * sizeof(char));
		printf("%s ", path);

		command *cmd = parse();
		command *orig = cmd;

		while (cmd)
		{
			if (cmd->size >= 1)
			{
				char **tokens = cmd->tokens;

				if (strcmp(tokens[0], "cd") == 0)
				{
					if (cmd->size < 2)
					{
						printf("No arguments for cd\n");
					}
					else
					{
						DIR *dir = opendir(tokens[1]);

						if (dir)
						{
							chdir(tokens[1]);
							closedir(dir);
						}
					}
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
					if (cmd->size > 0)
					{
						printf("%s: %s\n", tokens[0], strerror(errno));
					}
					else
					{
						printf("%s\n", strerror(errno));
					}
				}
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

	if (c)
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
