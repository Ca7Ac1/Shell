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

void leftRedirect(char **tokens, int size)
{
	if (size - 2 < 0 || strcmp(tokens[size - 2], "<") != 0)
	{
		run(tokens);
		return;
	}

	tokens[size - 2] = NULL;

	int in = open(tokens[size - 1], O_CREAT | O_RDONLY, 0644);
	dup2(in, STDIN_FILENO);

	run(tokens);

	dup2(extraIn, STDIN_FILENO);
	close(in);
}

void rightRedirect(char **tokens, int size)
{
	if (size - 2 < 0 || strcmp(tokens[size - 2], ">") != 0)
	{
		run(tokens);
		return;
	}

	tokens[size - 2] = NULL;

	int out;
	if (size - 3 >= 0 && strcmp(tokens[size - 3], ">") == 0)
	{
		out = open(tokens[size - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		tokens[size - 3] = NULL;
	}
	else
	{
		out = open(tokens[size - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}

	 
	dup2(out, STDOUT_FILENO);

	run(tokens);

	dup2(extraOut, STDOUT_FILENO);
	close(out);
}

void execute(char **tokens, int size)
{
	unsigned int amtPipes = 0;
	for (int i = 0; i < size; i++)
	{
		if (count(tokens[i], '|') > 0)
		{
			amtPipes++;
		}
	}

	if (amtPipes != 0)
	{
		char **curr = tokens;
		int **pipes = malloc(sizeof(int *) * amtPipes);

		int index = 0;
		int prevSize = 0;
		for (int i = 0; i < size; i++)
		{
			if (count(tokens[i], '|') > 0)
			{
				dup2(extraIn, STDIN_FILENO);
				dup2(extraOut, STDOUT_FILENO);

				pipes[index] = malloc(sizeof(int[2]));
				pipe(pipes[index]);

				tokens[i] = NULL;

				dup2(pipes[index][1], STDOUT_FILENO);

				if (index != 0)
				{
					dup2(pipes[index - 1][0], STDIN_FILENO);
                    close(pipes[index - 1][1]);
				}

				leftRedirect(curr, i - prevSize);

                if (index != 0)
                {
                    close(pipes[index - 1][0]);
                    free(pipes[index - 1]);
                }

				index++;
				prevSize = i + 1;
				curr = tokens + i + 1;
			}
		}



		dup2(pipes[index - 1][0], STDIN_FILENO);
		dup2(extraOut, STDOUT_FILENO);
        close(pipes[index - 1][1]);

		rightRedirect(curr, size - prevSize);


		// printf("%d\t%d\n", pipes[index - 1][0]);
		
		dup2(extraIn, STDIN_FILENO);
        close(pipes[index - 1][0]);

		free(pipes[index - 1]);

		free(pipes);
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (count(tokens[i], '<') > 0)
			{
				leftRedirect(tokens, size);
				return;
			}
		}

		rightRedirect(tokens, size);
	}
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

		if (errno)
		{
			printf("%s\n", strerror(errno));
		}

		exit(0);
	}
}
