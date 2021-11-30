#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
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

					errno = 0;
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
			existsLeftRedirect = 1;
			break;
		}
		else if (count(tokens[i], '>') > 0)
		{
			existsRightRedirect = 1;
			break;
		}
	}

	if (existsPipe)
	{
		pipeCmd(tokens, size);
	}
	else if (existsLeftRedirect)
	{
		leftRedirect(tokens, size);
	}
	else if (existsRightRedirect)
	{
		rightRedirect(tokens, size);
	}
	else
	{
		run(tokens);
	}
}

void leftRedirect(char **tokens, int size)
{
	tokens[size - 2] = NULL;

	int in = open(tokens[size - 1], O_CREAT | O_RDONLY, 0644);
	dup2(in, STDIN_FILENO);

	run(tokens);

	dup2(extraIn, STDIN_FILENO);
	close(in);
}

void rightRedirect(char **tokens, int size)
{
	tokens[size - 2] = NULL;

	int out = open(tokens[size - 1], O_CREAT | O_WRONLY, 0644);
	dup2(out, STDOUT_FILENO);

	run(tokens);

	dup2(extraOut, STDOUT_FILENO);
	close(out);
}

void pipeCmd(char **tokens, int size)
{
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		if (count(tokens[i], '|') > 0)
		{
			tokens[i] = 0;
		}
	}

	char *str = malloc(100000);
	str[0] = 0;

	for (int i = 0; i < index; i++)
	{
		strcat(str, )
	}

	free(str);
}

// void pipeCmd(char **tokens, int size)
// {
// 	int amt = 0;
// 	for (int i = 0; i < size; i++)
// 	{
// 		if (count(tokens[i], '|') > 0)
// 		{
// 			amt++;
// 		}
// 	}

// 	int pipes[2];
// 	pipe(pipes);

// 	char first = 1;
// 	char **curr = tokens;
// 	int currSize = 0;
// 	for (int i = 0; i <= size; i++)
// 	{
// 		if (i == size || count(tokens[i], '|') > 0)
// 		{
// 			currSize = i - currSize;

// 			dup2(extraOut, STDOUT_FILENO);
// 			dup2(extraIn, STDIN_FILENO);

// 			printf("%s\t%d\n", curr[0], amt);

// 			if (i != size)
// 			{
// 				tokens[i] = 0;
// 			}

// 			if (!first)
// 			{
// 				dup2(pipes[0], STDIN_FILENO);
// 			}
// 			else
// 			{
// 				for (int j = i; j < size && count(tokens[j], '|') == 0; j++)
// 				{
// 					if (count(tokens[j], '<') > 0)
// 					{
// 						leftRedirect(curr, currSize);
// 					}
// 				}

// 				first = 0;
// 			}

// 			if (amt)
// 			{
// 				run(curr);
// 				dup2(pipes[1], STDOUT_FILENO);
// 			}
// 			else
// 			{
// 				char redirect = 0;
// 				for (int j = i; j < size && count(tokens[j], '|') == 0; j++)
// 				{
// 					if (count(tokens[j], '>') > 0)
// 					{
// 						rightRedirect(curr, currSize);
// 						redirect = 1;
// 						break;
// 					}
// 				}

// 				if (!redirect)
// 				{
// 					run(curr);
// 				}
// 			}

// 			if (i + 1 < size)
// 			{
// 				curr = tokens + i + 1;
// 			}

// 			amt--;
// 		}
// 	}

// 	close(pipes[0]);
// 	close(pipes[1]);
// 	dup2(extraOut, STDOUT_FILENO);
// 	dup2(extraIn, STDIN_FILENO);
// }

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

		if (errno)
		{
			printf("%s\n", strerror(errno));
		}

		exit(0);
	}
}
