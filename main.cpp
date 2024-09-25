#include <stdio.h>
#include <stdlib.h>

#include "lines.h"
#include "quick_sort.h"
#include "file_process.h"
#include "TXLib.h"
#include "swap.h"

int main(int argc, char * argv[])
{
    if (argc == 4)
    {
        compare_func_t * comp = convert_comp(argv[3]);
        if (comp == NULL)
            return CMD_ERROR;

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
free_buf:
                free(onegin.lines);
                free(onegin.text_buf);
                fclose(out);
                fclose(in);
                return FILE_READ_ERROR;

            case MEMORY_ERROR:
                fprintf(stderr, "Error allocating memory.");
                goto free_buf;
                return MEMORY_ERROR;

            case SUCCESS:
                break;

            default:
                fprintf(stderr, "Something went wrong...");
                goto free_buf;
                return DEFAULT_ERROR;
        }

        printf("onegin.line_amount = %u\n", onegin.line_amount);

        string_struct * array = (string_struct*) calloc(sizeof(string_struct), onegin.line_amount);
        if (array == NULL)
        {
            fprintf(stderr, "Memory allocationg error for string_struct array");
            free(array);
            goto free_buf;
            return MEMORY_ERROR;
        }

        fill_string(&onegin, array);

        quick_sort(array, 0, onegin.line_amount -1, onegin.line_amount, sizeof(string_struct), comp);
        if(write_text(array, onegin.line_amount, out) == FILE_WRITE_ERROR)
        {
            fprintf(stderr, "Error writing to file %s", argv[2]);
            free(array);
            goto free_buf;
            return FILE_WRITE_ERROR;
        }

        free(array);
        goto free_buf;
    }
    else
    {
        fprintf(stderr, "debug <read_file> <out_file>, <compare_type>\n");
        fprintf(stderr, "                               forward\n");
        fprintf(stderr, "                               backward\n");
        fprintf(stderr, "                               forwardup\n");
        fprintf(stderr, "                               default\n");
    }

}
