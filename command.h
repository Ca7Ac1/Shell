#ifndef COMMAND_H
#define COMMAND_H

typedef struct command 
{
    char **tokens;
    int size;
    struct command *next;
} command;

command *addCommand(command *, char *);
void printCommands(command *);
void freeCommands(command *);

#endif
