#ifndef COMMAND_H
#define COMMAND_H

typedef struct command 
{
    char **tokens;
    int size;
    command *next;
} command;

command *addCommand(command *, char **);
void free(command *);

#endif
