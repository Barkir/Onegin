#include <stdio.h>

#include "quick_sort.h"

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
