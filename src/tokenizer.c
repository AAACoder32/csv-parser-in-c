#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "csv_string.h"

Token *make_token(char *str, int type)
{
    Token *token = (Token *)malloc(sizeof(Token));
    token->value = str;
    token->type = type;
    return token;
}

char *extract_text(char **ptr)
{
    String *str = create_str();
    while (**ptr != ',' && **ptr != '\"' && **ptr != '\r')
    {
        append_char(str, **ptr);
        (*ptr)++;
    }
    null_terminate(str);
    (*ptr)--;

    return str->data;
}

Token *move(char **ptr)
{
    if (**ptr == ',')
    {
        return make_token(",\0", COMMA);
    }

    if (**ptr == '\r')
    {
        (*ptr)++;
        if (**ptr == '\n')
        {
            return make_token("\r\n\0", NEWLINE);
        }
        (*ptr)--;
        return NULL;
    }

    if (**ptr == '\"')
    {
        (*ptr)++;
        if (**ptr == '\"')
        {
            return make_token("\"\"\0", DDQUOTE);
        }
        (*ptr)--;
        return make_token("\"\0", DQUOTE);
    }

    if (**ptr == '$')
    {
        return make_token("$\0", DOLLAR);
    }

    return make_token(extract_text(&(*ptr)), TEXTDATA);
}

LIST *tokenize(char **input)
{
    LIST *head = NULL;
    LIST *temp = NULL;

    head = (LIST *)malloc(sizeof(LIST));
    head->token = move(&(*input));
    (*input)++;
    head->next = NULL;

    if (**input != '\0')
    {
        temp = (LIST *)malloc(sizeof(LIST));
        temp->token = move(&(*input));
        temp->next = NULL;
        head->next = temp;
        (*input)++;
    }

    while (**input != '\0')
    {

        temp->next = (LIST *)malloc(sizeof(LIST));
        temp->next->token = move(&(*input));
        temp->next->next = NULL;
        temp = temp->next;
        (*input)++;
    }

    return head;
}

void traverse_list(LIST *head)
{
    LIST *temp = head;
    while (temp != NULL)
    {
        printf("-------------\n");
        printf("value:%s\n", temp->token->value);
        printf("type:%d\n", temp->token->type);
        printf("-------------\n");
        temp = temp->next;
    }
}