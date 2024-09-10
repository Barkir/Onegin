#ifndef LINES_H
#define LINES_H

struct text
{
    char ** lines;
    unsigned int size;

    char * text_buf;
};

enum err
{
    OK,
    ERR
};

void swap(char ** line1, char ** line2);
void text_sort(text * _text);
size_t file_size (FILE * file);
int linecmp(char * s1, char * s2);
int make_text(text * _text, FILE * file);
int count_lines(FILE * fp);
int min(int a, int b);

#endif
