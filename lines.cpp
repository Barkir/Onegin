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
    long int f_sz = file_size(file);
    printf("file_size = %ld\n", f_sz);
        if (f_sz == FILE_READ_ERROR)
        {
            fprintf(stderr, "File read error!\n");
            return FILE_READ_ERROR;
        }

    _text->line_amount = count_lines(file);

    _text->text_buf = (char*) calloc(f_sz + 1, sizeof(char));
    _text->text_buf[f_sz + 1] = '\0';
    if (_text->text_buf == NULL)
    {
        fprintf(stderr, "No memory allocated for text_buf!\n");
        return MEMORY_ERROR;
    }

    _text->lines = (char**) calloc(_text->line_amount, sizeof(char*));
    if (_text->text_buf == NULL)
    {
        fprintf(stderr, "No memory allocated for lines!\n");
        return MEMORY_ERROR;
    }

    size_t ret_code = fread(_text->text_buf, sizeof(char), f_sz, file);
    //printf("ret_code = %u\n", ret_code);
    if ((ret_code) != f_sz)
    {
        fprintf(stderr, "File read error!\n");
        fprintf(stderr, "ret_code = %ld, f_sz = %ld\n", ret_code, f_sz);
        return FILE_READ_ERROR;
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

    return SUCCESS;
}

int fill_string(text * _text, string_struct * string_)
{
    for (size_t i = 0; i < _text->line_amount; i++)
    {
        string_[i].start = _text->lines[i];
        string_[i].length = strlen(_text->lines[i]);
    }

    return SUCCESS;
}

int write_text(string_struct * string_, size_t size, FILE * file)
{
    for (unsigned int i = 0; i < size; i++)
    {
        fputs(string_[i].start, file);
        if (ferror(file))
            return FILE_WRITE_ERROR;
        fputs("\n", file);
            if (ferror(file))
                return FILE_WRITE_ERROR;
    }
}

int linecmp_backward(void * s1, void * s2)
{
    string_struct s1_ = *((string_struct *) s1);
    string_struct s2_ = *((string_struct *) s2);

    //printf("__LINECMP__\n");
    //printf("s1 = %s\n", s1_);
    //printf("s2 = %s\n\n", s2_);

    for (size_t i = s1_.length - 1, j = s2_.length - 1; i > 0 && j > 0; i--, j--)
    {
        while (s1_.start[i] < 'A' && s1_.start[i] > 0)
            i--;
        while(s2_.start[j] < 'A' && s2_.start[j] > 0)
            j--;
        if (toupper(s1_.start[i]) != toupper(s2_.start[j]))
            return (int) toupper(s1_.start[i]) - toupper(s2_.start[j]);
        else if (toupper(s1_.start[i]) == 0 && toupper(s2_.start[j]) == 0)
            return 0;
    }
    return 0;
}

int linecmp_forward(void * s1, void * s2)
{
    return strcmp(((string_struct*) s1)->start, ((string_struct*) s2)->start);
}

