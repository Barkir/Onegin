#ifndef LINES_H
#define LINES_H

struct text
{
    char ** lines;
    size_t line_amount;

    char * text_buf;
};

int make_text(text * _text, FILE * file);
void write_sorted_text(text * _text, FILE * file);
int linecmp_backward(void * s1, void * s2);
int linecmp_forward(void * s1, void * s2);
int min(int a, int b);

#endif
