#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "csv_file_reader.h"
#include "char_utils.h"

int LINE = 0;

FILE *open_csv(char *path)
{
    int len = strlen(path);
    char *c_ptr = &path[len - 4];
    char is_csv[5];
    for (int i = 0; i < 4; i++)
    {
        is_csv[i] = *c_ptr;
        c_ptr++;
    }
    c_ptr = NULL;
    is_csv[4] = '\0';
    if (strcmp(is_csv, ".csv") != 0)
    {
        printf("Error: requires .csv file\n");
        return NULL;
    }
    FILE *ptr = fopen(path, "rb");
    return ptr;
}

String *get_one_line(FILE *ptr)
{
    String *str = create_str();
    char c;
    LINE++;

    while ((c = fgetc(ptr)) != '\n')
    {
        if (c == '\r')
        {
            if ((c = fgetc(ptr)) == '\n')
            {
                append_char(str, '\r');
                append_char(str, c);
                break;
            }
            ungetc(c, ptr);
        }
        if (c == '\"')
        {
            push('\"');
            append_char(str, c);
            while ((c = fgetc(ptr)) != '\"')
            {
                append_char(str, c);
            }
            pop();
            if (!isempty())
            {
                printf("There is a missing \" in line %d\n", LINE);
                return NULL;
            }
        }
        append_char(str, c);
    }
    append_char(str, '$');
    null_terminate(str);
    return str;
}

STR_LIST *get_csv_data(FILE *ptr, int max_line)
{
    // STR_LIST *head = (STR_LIST*)malloc(sizeof(STR_LIST));
    // int count = 0;
    // String *str = get_one_line(ptr);
    
    while (fgetc(ptr) != EOF)
    {
        
    }

    return NULL;
}