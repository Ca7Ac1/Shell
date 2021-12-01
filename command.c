#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command.h"
#include "strlib.h"

command *addCommand(command *cmd, char *tokens)
{
    command *orig;
    if (!cmd)
    {
        cmd = malloc(sizeof(command));
        cmd->next = NULL;
        
        orig = cmd;
    }
    else
    {
        orig = cmd;

        while (cmd->next)
        {
            cmd = cmd->next;
        }
        
        cmd->next = malloc(sizeof(command));
        cmd = cmd->next;
    }

    int len = count(tokens, ' ') + 1;

    cmd->tokens = malloc(len * sizeof(char *) + sizeof(char *));

    int index = 0;
    while (tokens)
    {
        cmd->tokens[index] = strsep(&tokens, " ");
        index++;
    }   

    cmd->tokens[len] = NULL;

    cmd->size = len;
    cmd->next = NULL;
    
    return orig;
}

void printCommands(command *cmd)
{
    printf("Command [\n");

    while (cmd)
    {
        printf("size: %d ", cmd->size);

        for (int i = 0; i < cmd->size; i++)
        {
            printf("%s ", cmd->tokens[i]);
        }

        printf("\n");
        cmd = cmd->next;
    }

    printf("]\n");
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