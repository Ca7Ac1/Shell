#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "format.h"
#include "command.h"

command *parse()
{
    char line[(int) 3e5 + 1];
    fgets(line, (int) 3e5, stdin);
    
    char *formattedLine = format(line);

    command *commands = splitCommands(formattedLine);
    
    return commands;
}

command *splitCommands(char *line)
{
    command *commands;
    while (line)
    {   
        char *tokens = strsep(line, ';');
        commands = addCommand(commands, tokens);
    }
}

int main()
{
    parse();
}
