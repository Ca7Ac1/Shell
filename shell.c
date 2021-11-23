#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "shell.h"

void shell() {
	while (true) {
		char **tokens = parse();

        for (int i = 0; i < struct.size; i++)
        {
        switch tokens[i]:
		case "cd":
			break;
		case "exit:
			return;
		default:
			int c = fork();
			if(!c) execvp(tokens[0], tokens);
			break;
	    }
    }
}

void run()
{

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
