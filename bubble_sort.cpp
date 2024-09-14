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

void quick_sort(void * data, int low, int high, size_t data_size, size_t el_size, compare_func_t compare_func)
{
    if (low < high)
    {
        int iteration = quick_sort_iteration(data, low, high, data_size, el_size, compare_func);
        quick_sort(data, low, iteration - 1, data_size, el_size, compare_func);
        quick_sort(data, iteration + 1, high, data_size, el_size, compare_func);
    }
}

int quick_sort_iteration(void * data, int low, int high, size_t data_size, size_t el_size, compare_func_t compare_func)
{
    void * pivot = data + high * el_size;
    int x = low - 1;

    for (int y = low; y <= high - 1; y++)
    {
        if (compare_func(data + y * el_size, pivot) < 0)
        {
            x++;
            swap((void**)(data + x * el_size), (void**)(data + y * el_size));
        }
    }
    swap((void**)(data + (x + 1) * el_size), (void**)(data + high * el_size));
    return x + 1;
}


void swap(void ** el1, void ** el2)
{
    //printf("__SWAPFUNC__\n");
    //printf("el1 = %d, el2 = %d\n", *el1, *el2);
    void * tmp = *el1;
    //printf("TMP = %d ", tmp);
    *el1 = *el2;
    //printf("el1 = %d ", *el1);
    *el2 = tmp;
    //printf("el2 = %d\n", *el2);
}
