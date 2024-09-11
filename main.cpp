#include <stdio.h>
#include <stdlib.h>

#include "lines.h"
#include "TXLib.h"

int main(void)
{
    FILE * fp = fopen("onegin.txt", "r");                       // file with text
    FILE * out = fopen("sorted_onegin.txt", "w");               // file for output

    text onegin = {};                                           // struct containing text

    if (make_text(&onegin, fp) == ERR)                          // error handling and creating a structure
    {
        fprintf(stderr, "Something went wrong...");
        return ERR;
    }

    text_sort(END, &onegin);                                    // sorting text
    write_sorted_text(&onegin, out);                            // writing text in a file

    free(onegin.lines);                                         // cleaning all the buffers
    free(onegin.text_buf);                                      // closing files
    fclose(fp);
    fclose(out);
}
