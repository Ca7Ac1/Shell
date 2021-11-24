#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "shell.h"
#include "command.h"

void shell() {
	while (true) {
		command* command = parse();
		char** tokens = command.cmd;


	        for (int i = 0; i < command.size; i++)
	       	{
			//create separate function
			//int start = 0
			
			//TODO: find tokens[i].size ie length of cmd + flags
			for(int j = 0; j < tokens[i].size; j++) {
				if(strcmp(tokens[i][j], ">") == 0) {
					rrun1(tokens, j);	
				} else if(strcmp(tokens[i][j], "<") == 0) {
					rrun2(tokens, j);
				}
			}


		       	if (strcmp(tokens[i], "cd") == 0) {
	
			} else if (strcmp(tokens[i], "exit") == 0) {
				return;
			} else {
				run(tokens);
			}
    		}
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
