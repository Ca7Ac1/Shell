#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command.h"

command *addCommand(command *cmd, char *tokens)
{
    command *orig = cmd;

    while (cmd->next)
    {
        cmd = cmd->next;
    }

    cmd->next = malloc(sizeof(cmd));
    cmd = cmd->next;

    int len = 0;
    for (int i = 0; i < strlen(tokens); i++)
    {
        if (tokens[i] == ' ')
        {
            len++;
        }
    }

    char **sepTokens = malloc(len * sizeof(char *));

    int index = 0;
    while (tokens)
    {
        char* token = strsep(&tokens, " ");
        sepTokens[index] = token;

        index++;
    }   

    
    cmd->size = len;
    cmd->tokens = sepTokens;
    
    return orig;
}

void freeCommands(command *cmd)
{
    command *prev;

    free(cmd->tokens[0]);
    free(cmd->tokens);

    while (cmd)
    {
        prev = cmd;
        cmd = cmd->next;

        free(prev);
    }
}