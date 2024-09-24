#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

typedef int compare_func_t (void * a, void * b);

void bubble_sort(void * data, size_t data_size, size_t el_size, compare_func_t compare_func);
void uswap(void * el1, void * el2, size_t el_size);


#endif
