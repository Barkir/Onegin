#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lines.h"
#include <assert.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

size_t file_size (FILE * file)
{
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    return size;
}

int linecmp(char * s1, char * s2)
{
    for (int i = strlen(s1) - 1, j = strlen(s2) - 1; i > 0 && j > 0; i--, j--)
    {
        while (s1[i] < 'A' && s1[i] > 0)
            i--;
        while(s2[j] < 'A' && s2[j] > 0)
            j--;

        if (toupper(s1[i]) != toupper(s2[j]))
            return (int) toupper(s1[i]) - toupper(s2[j]);
        else if (toupper(s1[i]) == 0 && toupper(s2[j]) == 0)
            return 0;
    }

    return 0;
}

int count_lines(FILE * fp)
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

int make_text(text * _text, FILE * file)
{
    const unsigned int f_sz = file_size(file);
        if (f_sz == ERR)
        {
            fprintf(stderr, "File read error!\n");
            return ERR;
        }

    _text->size = count_lines(file);

    _text->text_buf = (char*) calloc(f_sz, sizeof(char));
    if (_text->text_buf == NULL)
    {
        fprintf(stderr, "No memory allocated for text_buf!\n");
        return ERR;
    }

    _text->lines = (char**) calloc(_text->size, sizeof(char*));
    if (_text->text_buf == NULL)
    {
        fprintf(stderr, "No memory allocated for lines!\n");
        return ERR;
    }

    const unsigned int ret_code = fread(_text->text_buf, sizeof(char), f_sz, file);
    if ((ret_code + _text->size) != f_sz)
    {
        fprintf(stderr, "File read error!\n");
        fprintf(stderr, "ret_code = %u, f_sz = %u\n", ret_code, f_sz);
        return ERR;
    }
    fprintf(stderr, "File read success!\n");


    for (unsigned int i = 1, j = 1; i < ret_code; i++)
    {
        if (_text->text_buf[i - 1] == '\0')
        {
            _text->lines[j] = &(_text->text_buf[i]);
            if (j == _text->size)
                break;
            j++;
        }
        if (_text->text_buf[i] == '\n')
            _text->text_buf[i] = '\0';
    }
    _text->lines[0] = _text->text_buf;

    return OK;

}

void text_sort(text * _text)
{
    bool swapped;
    for (unsigned int i = 0; i < _text->size; i++)
    {
        swapped = false;
        for (unsigned int j = 0; j < _text->size - i - 1; j++)
        {
            if (linecmp(_text->lines[i], _text->lines[j]) < 0)
            {
                //printf("%s <> %s\n", _text->lines[i], _text->lines[j]);
                swap(&(_text->lines[i]), &(_text->lines[j]));
                //printf("%s ! %s\n\n", _text->lines[i], _text->lines[j]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}


void swap(char ** line1, char ** line2)
{
    char * tmp = 0;
    tmp = *line1;
    *line1 = *line2;
    *line2 = tmp;
}


