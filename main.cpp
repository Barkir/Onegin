#include <stdio.h>
#include <stdlib.h>

#include "lines.h"
#include "TXLib.h"

int main(void)
{
    FILE * fp = fopen("onegin.txt", "r");

    text onegin = {};

    if (make_text(&onegin, fp) == ERR)
    {
        fprintf(stderr, "Something went wrong...");
        return ERR;
    }

    text_sort(&onegin);
    for (unsigned int i = 0; i < onegin.size; i++)
        printf("%s\n", onegin.lines[i]);

    free(onegin.lines);
    free(onegin.text_buf);
    fclose(fp);
}
