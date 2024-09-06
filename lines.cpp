#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lines.h"

#define min(a, b) a > b ? a : b

int compare_str(char * s1, char * s2)
{
    for (int i = 0, j = 0; i < (min(strlen(s1), strlen(s2)) + 1); i++, j++)
    {
        if (s1[i] != s2[j])
            return (int) s1[i] - s2[j];
        else if (s1[i] == 0 && s2[j] == 0)
            return 0;
    }
}


