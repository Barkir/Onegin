#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "quick_sort.h"
#include "swap.h"

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
            uswap((data + x * el_size), (data + y * el_size), el_size);
        }
    }
    uswap((data + (x + 1) * el_size), (data + high * el_size), el_size);
    return x + 1;
}

