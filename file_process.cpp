#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_process.h"

long int file_size (FILE * file)                              // returns a file size (number of chars)
{
    fseek(file, 0L, SEEK_END);
    if (ferror(file))
        return FILE_READ_ERROR;
    long int size = ftell(file);
    printf("size = %ld\n", size);
    if (size == -1L)
        return FILE_READ_ERROR;
    rewind(file);
    return size;
}

size_t count_lines(FILE * fp)                               // counts the number of lines in file
{
    int counter = 0;
    const int size = 100;

    char line[size] = "";

    if (fp == NULL)
    {
        fprintf(stderr, "Error reading file!\n");
        return FILE_READ_ERROR;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
        counter++;

    rewind(fp);

    return counter;
}

void clean_file(char * arg)
{
    char start[100] = "python clean_file.py ";
    const char * command = strcat(start, arg);
    system(command);
}
