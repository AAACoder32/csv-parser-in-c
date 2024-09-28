#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str_stack.h"

// Global variable for stack
STACK *S_TOP = NULL;

// Push str or array of chars
void push_str(char *str)
{
    STACK *n = (STACK *)malloc(sizeof(STACK));
    if (isfull_str())
    {
        printf("Stack overflow!");
        return;
    }
    n->value = str;
    n->next = S_TOP;
    S_TOP = n;
}

// Pop str from stack
char *pop_str()
{
    if (isempty_str())
    {
        printf("Stack underflow!");
        return "\0";
    }
    STACK *n = S_TOP;
    char *v = n->value;
    S_TOP = S_TOP->next;
    free(n);
    return v;
}

int isempty_str()
{
    if (S_TOP == NULL)
    {
        return 1;
    }
    return 0;
}

// See top str of stack
char *peek_str()
{
    if (isempty_str())
    {
        printf("Stack underflow!");
        return "\0";
    }
    return S_TOP->value;
}

int isfull_str()
{
    STACK *n = (STACK *)malloc(sizeof(STACK));
    if (n == NULL)
    {
        return 1;
    }
    return 0;
}
