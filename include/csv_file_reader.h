#ifndef CSV_FILE_READER
#define CSV_FILE_READER

#include <stdio.h>
#include "csv_string.h"

// Data list data struct
typedef struct STR_LIST
{
    String *data;
    struct STR_LIST *next;
} STR_LIST;

extern int LINE;

// Initilaize file pointer
FILE *open_csv(char *path);

// Give one line of data
String *get_one_line(FILE *ptr);

// Give all data as a list
STR_LIST *get_csv_data(FILE *ptr, int max_line);

#endif