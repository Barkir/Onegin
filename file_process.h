#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

size_t file_size (FILE * file);
size_t count_lines(FILE * fp);

enum err
{
    OK,
    ERR
};

#endif
