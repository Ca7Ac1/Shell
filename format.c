#include <stdlib.h>
#include <stdio.h>

#include "format.h"

char *removeSpace(char *line)
 18 {
 19     char *newLine = malloc (sizeof(*line) * strlen(line));
 20 
 21 
 22     int index = 0;
 23     for (int i = 0; i < strlen(line); i++)
 24     {
 25         if (!(line[i] == ' ' && (i == 0 || line[i - 1] == ' ')))
 26         {
 27             newLine[index] = line[i];
 28             index++;
 29         }
 30     }
 31 
 32     newLine[index] = '\0';
 33 
 34     return newLine;
 35 }

