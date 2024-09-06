#include <stdio.h>

#include "lines.h"

int main(void)
{
    char line1[] = "hello my name is";
    char line2[] = "hello my name is";

    int result = compare_str(line1, line2);
    printf("%d", result);
}
