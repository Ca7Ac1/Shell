#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "format.h"

char ***parse()
{
    char line[(int) 3e5 + 1];
    fgets(line, (int) 3e5, stdin);
    
    char *newLine = removeSpace(line); 
    
}
