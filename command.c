#include <stdlib.h>
#include <stdio.h>

#include "command.h"

command *addCommand(command *cmd, char *tokens)
{
    cmd *orig = cmd;

    while (cmd->next)
    {
        cmd = cmd->next;
    }

    cmd->next = malloc(sizeof(cmd));
    cmd = cmd->next;

    int len = 0;
    for (int i = 0; i < strlen(cmd); i++)
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
        char* token = strsep(tokens, ' ');
        sepTokens[index] = token;

        index++;
    }   

    
    cmd->len = len;
    cmd->tokens = sepTokens;
    
    return orig;
}

void free(command *cmd)
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