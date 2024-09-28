#include <stdlib.h>
#include "csv_string.h"

// Create new string
String *create_str()
{
    String *str = (String *)malloc(sizeof(String));
    str->capacity = 10; // Initial capacity
    str->length = 0;
    str->data = malloc(str->capacity);
    return str;
}

// append a character to the string
void append_char(String *str, char c)
{
    if (str->length == str->capacity)
    {
        str->capacity += str->capacity / 4;
        str->data = realloc(str->data, str->capacity);
    }
    str->data[str->length] = c;
    str->length++;
}

// null-terminate the string
void null_terminate(String *str)
{
    str->data[str->length] = '\0';
}