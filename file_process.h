#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

enum errors
{
    FILE_OPEN_ERROR,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    MEMORY_ERROR,
    DEFAULT_ERROR,
    CMD_ERROR,
    SUCCESS

};

enum compare_enum
{
    FORWARD,
    FORWARDUP,
    BACKWARD,
    DEFAULT
};

long int file_size (FILE * file);
size_t count_lines(FILE * fp);
void clean_file(char * arg);
int convert_comp(char * arg);

#endif
