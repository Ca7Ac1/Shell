#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "format.h"

char *lower(char *line)
{
    for (int i = 0; i < strlen(line); i++)
    {
        line[i] = tolower(line[i]);
    }

    return line;
}

char *insertSpace(char *line)
{
    int additions = 0;

    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '|' || line[i] == '>' || line[i] == '<')
        {
            additions++;
        }
    }

    additions *= 2;

    char *newLine = malloc(sizeof(char) * strlen(line) + sizeof(char) * additions + 1);

    int index = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '|' || line[i] == '>' || line[i] == '<') 
        {
            newLine[index] = ' ';
            newLine[index + 1] = line[i];
            newLine[index + 2] = ' ';

            index += 2; 
        }
        else
        {
            newLine[index] = line[i];
        }

        index++;
     }

    newLine[index] = '\0';

    return newLine;
}

char *alterSpace(char *line)
{
    char *newLine = malloc(sizeof(char) * strlen(line));
  
    int index = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '\t' || line[i] == '\n')
        {
            newLine[i] = ' ';
        }
        else
        {
            newLine[i] = line[i];
        }
    }

    newLine[strlen(line)] = '\0';
  
    return newLine;
}

char *removeSpace(char *line)
{
    char *newLine = malloc(sizeof(char) * strlen(line) + 1);
  
    int index = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (index != 0 && newLine[index - 1] == ' ' && (line[i] == ';' || index == 1))
        {
            newLine[index - 1] = line[i];
        }
        else if (index != 0 && line[i] != ' ' || (newLine[index - 1] != ' ' && newLine[index - 1] != ';'))
        {
            newLine[index] = line[i];
            index++;
        }
    }
  
    while (index > 0 && newLine[index - 1] == '\n' || newLine[index - 1] == ' ')
    {
        index--;
    }

    newLine[index] = '\0';
  
    return newLine;
}

char *format(char* line)
{
    // line = lower(line);
    char *insert = insertSpace(line);
    char *alter = alterSpace(insert);
    char *remove = removeSpace(alter);

    free(insert);
    free(alter);
    
    return remove;
}

