#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "format.h"

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

    char *newLine = malloc(sizeof(*line) * strlen(line) + sizeof(char) * additions);

    int index = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ';' || line[i] == '|' || line[i] == '>' || line[i] == '<') 
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

    return newLine;
}

char *removeSpace(char *line)
{
    char *newLine = malloc(sizeof(*line) * strlen(line));
  
    int index = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (!(line[i] == ' ' && (i == 0 || line[i - 1] == ' ')))
        {
            newLine[index] = line[i];
            index++;
        }
    }
  
    if (index > 0 && newLine[index - 1] == '\n')
    {
        index--;
    }

    newLine[index] = '\0';
  
    return newLine;
}

