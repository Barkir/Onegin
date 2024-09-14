#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lines.h"
#include "file_process.h"

int min(int a, int b)                                                                                   // returns min number out of a, b
{
    return a > b ? b : a;
}

int make_text(text * _text, FILE * file)                                                                // creates a text structure (text buffer, line buffer, line buffer size)
{
    size_t f_sz = file_size(file);
    printf("file_size = %u\n", f_sz);
        if (f_sz == ERR)
        {
            fprintf(stderr, "File read error!\n");
            return ERR;
        }

    _text->line_amount = count_lines(file);

    _text->text_buf = (char*) calloc(f_sz + 1, sizeof(char));
    _text->text_buf[f_sz + 1] = '\0';
    if (_text->text_buf == NULL)
    {
        fprintf(stderr, "No memory allocated for text_buf!\n");
        return ERR;
    }

    _text->lines = (char**) calloc(_text->line_amount, sizeof(char*));
    if (_text->text_buf == NULL)
    {
        fprintf(stderr, "No memory allocated for lines!\n");
        return ERR;
    }

    size_t ret_code = fread(_text->text_buf, sizeof(char), f_sz, file);
    //printf("ret_code = %u\n", ret_code);
    if ((ret_code) != f_sz)
    {
        fprintf(stderr, "File read error!\n");
        fprintf(stderr, "ret_code = %u, f_sz = %u\n", ret_code, f_sz);
        return ERR;
    }

    fprintf(stderr, "File read success!\n");

    _text->lines[0] = _text->text_buf;
    for (unsigned int i = 0, j = 1; i < ret_code; i++)          // strchr()
    {
        if (_text->text_buf[i - 2] == '\0' && _text->text_buf[i - 1] == '\0' && i != 0 && i != 1)
        {
            _text->lines[j] = &(_text->text_buf[i]);
            if (j == _text->line_amount)
                break;
            j++;
        }
        if (_text->text_buf[i] == '\n' || _text->text_buf[i] == '\r')
            _text->text_buf[i] = '\0';
    }

    return OK;
}

void write_sorted_text(text * _text, FILE * file)
{
    for (unsigned int i = 0; i < _text->line_amount; i++)
    {
        fputs(_text->lines[i], file);
        fputs("\n", file);
    }
}

int linecmp_backward(void * s1, void * s2)
{
    char * s1_ = *((char **) s1);
    char * s2_ = *((char **) s2);
    //printf("__LINECMP__\n");
    //printf("s1 = %s\n", s1_);
    //printf("s2 = %s\n\n", s2_);
    for (size_t i = strlen(s1_) - 1, j = strlen(s2_) - 1; i > 0 && j > 0; i--, j--)
    {
        while (s1_[i] < 'A' && s1_[i] > 0)
            i--;
        while(s2_[j] < 'A' && s2_[j] > 0)
            j--;
        if (toupper(s1_[i]) != toupper(s2_[j]))
            return (int) toupper(s1_[i]) - toupper(s2_[j]);
        else if (toupper(s1_[i]) == 0 && toupper(s2_[j]) == 0)
            return 0;
    }
    return 0;
}

int linecmp_forward(void * s1, void * s2)
{
    return strcmp(*(char**)s1, *(char**)s2);
}

