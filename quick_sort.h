#ifndef QUICK_SORT_H
#define QUICK_SORT_H

typedef int compare_func_t (void * a, void * b);

void quick_sort(void * data, int low, int high, size_t data_size, size_t el_size, compare_func_t compare_func);
int quick_sort_iteration(void * data, int low, int high, size_t data_size, size_t el_size, compare_func_t compare_func);
void swap(void ** el1, void ** el2);

#endif
