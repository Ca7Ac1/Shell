#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "format.h"
#include "command.h"

command *parse()
{
    char line[300001];
    fgets(line, 300000 * sizeof(char), stdin);
    
    char *formattedLine = format(line);

    command *commands = splitCommands(formattedLine);
    
    return commands;
}

command *splitCommands(char *line)
{
    command *commands = NULL;
    while (line)
    {   
        char *tokens = strsep(&line, ";");
        commands = addCommand(commands, tokens);
    }

    return commands;
}