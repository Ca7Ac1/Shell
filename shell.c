#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>

#include "parser.h"
#include "shell.h"
#include "command.h"
#include "strlib.h"

int extraIn;
int extraOut;

void shell()
{
	extraIn = dup(STDIN_FILENO);
	extraOut = dup(STDOUT_FILENO);

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
					execute(tokens, cmd->size);
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

void execute(char **tokens, int size)
{
	char existsLeftRedirect = 0;
	char existsRightRedirect = 0;
	char existsPipe = 0;
	for (int i = 0; i < size; i++)
	{
		if (count(tokens[i], '|') > 0)
		{
			existsPipe = 1;
			break;
		}
		else if (count(tokens[i], '<') > 0)
		{
			existsRightRedirect = 1;
			break;
		}
		else if (count(tokens[i], '>') > 0)
		{
			existsLeftRedirect = 1;
			break;
		}
	}

	if (existsLeftRedirect)
	{
		leftRedirect(tokens, size);
	}
	else if (existsRightRedirect)
	{
		rightRedirect(tokens, size);
	}
	else if (existsPipe)
	{
		pipeCmd(tokens, size);
	}
	else
	{
		run(tokens);
	}
}

void leftRedirect(char **tokens, int size)
{
	tokens[size - 2] = NULL;

	int in = open(tokens[size - 1], O_CREAT, 0644);
	dup2(in, STDIN_FILENO);

	run(tokens);

	dup2(extraIn, STDIN_FILENO);
	close(in);
}

void rightRedirect(char **tokens, int size)
{
	tokens[size - 2] = NULL;

	int out = open(tokens[size - 1], O_CREAT, 0644);
	dup2(out, STDOUT_FILENO);

	run(tokens);

	dup2(extraOut, STDOUT_FILENO);
	close(out);
}

void pipeCmd(char **tokens, int size)
{

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
