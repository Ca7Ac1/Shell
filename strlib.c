#include <string.h>

#include "strlib.h"

int count(char *str, char target)
{
    int amt = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == target)
        {
            amt++;
        }
    }

    return amt;
}