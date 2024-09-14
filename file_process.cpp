#include <stdio.h>

#include "file_process.h"

size_t file_size (FILE * file)                              // returns a file size (number of chars)
{
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
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
        return ERR;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
        counter++;

    rewind(fp);

    return counter;
}
