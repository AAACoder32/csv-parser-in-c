#ifndef PARSER
#define PARSER

// Non-terminal list
typedef struct VAR_LIST
{
    char *str;
    struct VAR_LIST *prev;
    struct VAR_LIST *next;
} VAR_LIST;

// extract non-terminal
// (This is parser specific only which extracts this type of string <text>)
VAR_LIST *extract_var(const char *input);

// CSV LL(1) parsing table
extern const char *LL1_TABLE[12][6];

// Parser function
int parse(LIST *head);

// Get table index of non-terminal 
int get_index(char *str);

#endif