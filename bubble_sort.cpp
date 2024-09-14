#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "bubble_sort.h"
#include "lines.h"

void bubble_sort(void * data, size_t data_size, size_t el_size, compare_func_t compare_func)
{
    bool swapped;

    //printf("data_size = %d\n", data_size);
    for (size_t i = 0; i < data_size; i++)
    {
        //printf("&data[%d] = %d\n", i, data + i * el_size);
        //printf("el_size = %u\n", el_size);
        swapped = false;
        for (size_t j = 0; j < data_size - i - 1; j++)
        {
            if (compare_func((data + i * el_size), (data + j * el_size)) < 0)
            {
                //printf("unswapped:\n &data[%d] = %d\n &data[%d] = %d\n\n", i, data + i * el_size, j, data + j * el_size);
                swap((void**)(data + i * el_size), (void**)(data + j * el_size));
                //printf("swapped:\n &data[%d] = %d\n &data[%d] = %d\n\n", i, data + i * el_size, j, data + j * el_size);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}

void swap(void * el1, void * el2, size_t el_size)
{
    char * buf = (char*) calloc(el_size, sizeof(char));
    memcpy(buf, el1, el_size);
    memcpy(el1, el2, el_size);
    memcpy(el2, buf, el_size);
}
