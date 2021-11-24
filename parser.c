#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "format.h"
#include "tokens.h"

token *parse()
{
    char line[(int) 3e5 + 1];
    fgets(line, (int) 3e5, stdin);
    
    char *newLine = insertSpace(line);
    newLine = removeSpace(newLine); 
    
    int len = 0;
    for (int i = 0; i < strlen(newLine); i++)
    {
        if (newLine[i] == ';' || newLine[i] == '\n')
        {
            len++;
        }
    }

    token *commands = malloc(sizeof(token) * len);
    
    int index = 0;
    while (*newLine)
    {
        commands[index] = createToken();
    }
}

token *createToken(char *)
{

}

int main()
{
    parse();
}
