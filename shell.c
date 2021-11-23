#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "shell.h"

void shell() {
	while (true) {
		char **tokens = parse();

	        for (int i = 0; i < struct.size; i++)
	       	{
			//create separate function
			//int start = 0
			for(int j = 0; j < struct[i].size; j++) {
				//can u have multiple redirections
				if(strcmp(struct[i][j], ">") == 0) {
					rrun(tokens, j);	
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

void run(token tokens)
{
	int c = fork();
	if(!c) {
		execvp(tokens[0], tokens);
	}
}

void rrun(token tokens, int r) {
	char** first;
	for(int i = 0; i < j; i++) {
		first[i] = tokens[i];	
	}
	//TODO: finish plz
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
