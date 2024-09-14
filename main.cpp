#include <stdio.h>
#include <stdlib.h>

#include "lines.h"
#include "quick_sort.h"
#include "file_process.h"
#include "TXLib.h"

int main(void)
{
    int a = 1;
    int b = 2;

    swap(&a, &b, sizeof(int));
    printf("a = %d, b = %d\n", a, b);

    FILE * in = fopen("onegin.txt", "rb");                                                                              // file with text
    FILE * out = fopen("sorted_onegin.txt", "wb");                                                                      // file for output

    text onegin = {};                                                                                                   // struct containing text

    if (make_text(&onegin, in) == ERR)                                                                                  // error handling and creating a structure
    {
        fprintf(stderr, "Something went wrong...");
        return ERR;
    }
    printf("onegin.line_amount = %u\n", onegin.line_amount);
    // printf("___UNSORTED LINES___\n");
    // for (int i = 0; i < 11; i++)
    //     printf("onegin.lines[%d] = %d\n", i, onegin.lines + i);
    // printf("-------------------\n");
    quick_sort(onegin.lines, 0, onegin.line_amount - 1, onegin.line_amount, sizeof(char*), linecmp_backward);                                     // bubble_sort for text lines (you can write your own compare func and use it)
    write_sorted_text(&onegin, out);                                                                                    // writes sorted text in file
    // printf("____SORTED LINES______\n");
    // for (int i = 0; i < 11; i++)
    //     printf("onegin.lines[%d] = %d\n", i, onegin.lines + i);

    free(onegin.lines);                                                                                                 // cleaning all the buffers
    free(onegin.text_buf);                                                                                              // closing files
    fclose(in);
    fclose(out);
}
