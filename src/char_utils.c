#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "char_utils.h"

// Global variable for stack
S_Node *TOP = NULL;

// Reverse string without changing it in place
char *reverse_string(const char *str)
{
    int length = strlen(str);
    char *reversed = malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++)
    {
        reversed[length - i - 1] = str[i];
    }
    reversed[length] = '\0';
    return reversed;
}

// Push char or array of chars
void push(char str)
{
    S_Node *n = (S_Node *)malloc(sizeof(S_Node));
    if (isfull())
    {
        printf("Stack overflow!");
        return;
    }
    n->value = str;
    n->next = TOP;
    TOP = n;
}

// Pop char from stack
char pop()
{
    if (isempty())
    {
        printf("Stack underflow!");
        return '\0';
    }
    S_Node *n = TOP;
    char v = n->value;
    TOP = TOP->next;
    free(n);
    return v;
}

int isempty()
{
    if (TOP == NULL)
    {
        return 1;
    }
    return 0;
}

// See top char of stack
char peek()
{
    if (isempty())
    {
        printf("Stack underflow!");
        return '\0';
    }
    return TOP->value;
}

int isfull()
{
    S_Node *n = (S_Node *)malloc(sizeof(S_Node));
    if (n == NULL)
    {
        return 1;
    }
    return 0;
}
