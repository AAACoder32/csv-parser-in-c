#ifndef CSV_STRING
#define CSV_STRING

// Define a struct to represent string
typedef struct String
{
    char *data;
    int capacity;
    int length;
} String;

// create a new string
String *create_str();

// append a character to the string
void append_char(String *str, char c);

// null-terminate the string
void null_terminate(String *str);

#endif