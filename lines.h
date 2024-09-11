#ifndef LINES_H
#define LINES_H

struct text
{
    char ** lines;
    unsigned int line_amount;

    char * text_buf;
};

enum err
{
    OK,
    ERR
};

enum sort_type
{
    START,
    END
};

void swap(char ** line1, char ** line2);
void text_sort(int sort_type, text * _text);
size_t file_size (FILE * file);
int linecmp(int sort_type, char * s1, char * s2);
int make_text(text * _text, FILE * file);
int count_lines(FILE * fp);
int min(int a, int b);
void write_sorted_text(text * _text, FILE * file);

#endif
