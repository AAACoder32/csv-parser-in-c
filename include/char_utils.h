#ifndef UTILS
#define UTILS

// Reverse string without changing it in place
char *reverse_string(const char *str);

// char stack for implementing LL(1) parser
typedef struct S_Node
{
    char value;
    struct S_Node *next;
} S_Node;

// Push char or array of chars
void push(char str);

// Pop char from stack
char pop();

// Check is empty or not
int isempty();

// Check stack is full
int isfull();

// See top char of stack
char peek();

extern S_Node *TOP;

#endif