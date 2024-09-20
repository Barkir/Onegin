#ifndef LINES_H
#define LINES_H

struct text
{
    char ** lines;
    size_t line_amount;

    char * text_buf;
};

struct string_struct
{
    const char * start;
    size_t length;
};

int make_text(text * _text, FILE * file);
int write_text(string_struct * _my_string, size_t size, FILE * file);
int linecmp_backward(void * s1, void * s2);
int linecmp_forward(void * s1, void * s2);
int linecmp_forwardup(void * s1, void * s2);
int fill_string(text * _text, string_struct * _string);
int min(int a, int b);

#endif
