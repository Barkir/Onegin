#include <stdio.h>
#include <stdlib.h>

#include "lines.h"
#include "quick_sort.h"
#include "file_process.h"
#include "TXLib.h"

int main(int argc, char * argv[])
{

    if (argc == 3)
    {
        clean_file(argv[1]);

        FILE * in = fopen(argv[1], "rb");
        if (in == NULL)
        {
            printf("Error opening file %s", argv[1]);
            fclose(in);
            return FILE_OPEN_ERROR;
        }

        FILE * out = fopen(argv[2], "wb");
        if (out == NULL)
        {
            printf("Error opening file %s", argv[2]);
            fclose(out);
            return FILE_OPEN_ERROR;
        }

        text onegin = {};
        int result = make_text(&onegin, in);
        switch(result)
        {
            case FILE_READ_ERROR:
                fprintf(stderr, "Error reading file.");
                free(onegin.lines);
                free(onegin.text_buf);
                fclose(out);
                fclose(in);
                return FILE_READ_ERROR;

            case MEMORY_ERROR:
                fprintf(stderr, "Error allocating memory.");
                free(onegin.lines);
                free(onegin.text_buf);
                fclose(out);
                fclose(in);
                return MEMORY_ERROR;

            case SUCCESS:
                break;

            default:
                fprintf(stderr, "Something went wrong...");
                free(onegin.lines);
                free(onegin.text_buf);
                fclose(out);
                fclose(in);
                return DEFAULT_ERROR;
        }

        printf("onegin.line_amount = %u\n", onegin.line_amount);

        string_struct * array = (string_struct*) calloc(sizeof(string_struct), onegin.line_amount);
        if (array == NULL)
        {
            fprintf(stderr, "Memory allocationg error for string_struct array");
            free(array);
            free(onegin.lines);
            free(onegin.text_buf);
            fclose(in);
            fclose(out);
            return MEMORY_ERROR;
        }

        fill_string(&onegin, array);

        // for (size_t i = 0; i < onegin.line_amount; i++)
        // {
        //     printf("len = %u, string = %10s\n", array[i].length, array[i].start);
        // }

        // printf("___UNSORTED LINES___\n");
        // for (int i = 0; i < 11; i++)
        //     printf("onegin.lines[%d] = %d\n", i, onegin.lines + i);
        // printf("-------------------\n");

        quick_sort(array, 0, onegin.line_amount -1, onegin.line_amount, sizeof(string_struct), linecmp_backward);
        if(write_text(array, onegin.line_amount, out) == FILE_WRITE_ERROR)
        {
            fprintf(stderr, "Error writing to file %s", argv[2]);
            free(array);
            free(onegin.lines);
            free(onegin.text_buf);
            fclose(in);
            fclose(out);
            return FILE_WRITE_ERROR;
        }

        // printf("____SORTED LINES______\n");
        // for (int i = 0; i < 11; i++)
        //     printf("onegin.lines[%d] = %d\n", i, onegin.lines + i);


        free(array);
        free(onegin.lines);
        free(onegin.text_buf);
        fclose(in);
        fclose(out);
    }

    else
    {
        fprintf(stderr, "debug <read_file> <out_file>");
        return CMD_ERROR;
    }
}
