#ifndef STR_STACK
#define STR_STACK

// char stack for implementing LL(1) parser
typedef struct STACK
{
    char *value;
    struct STACK *next;
} STACK;

// Push char or array of chars
void push_str(char *str);

// Pop char from stack
char *pop_str();

// Check is empty or not
int isempty_str();

// Check stack is full
int isfull_str();

// See top char of stack
char *peek_str();

extern STACK *S_TOP;

#endif