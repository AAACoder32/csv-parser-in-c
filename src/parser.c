#include "tokenizer.h"
#include "parser.h"
#include "str_stack.h"
#include "csv_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char *LL1_TABLE[12][6] =
    {{"<header_><record><record_><CRLF_>\0", "<header_><record><record_><CRLF_>\0", "<header_><record><record_><CRLF_>\0", "error\0", "<header_><record><record_><CRLF_>\0", "\0"},
     {"<name><name_>\0", "<name><name_>\0", "<name><name_>\0", "error\0", "\0", "error\0"},
     {"<header><CRLF>\0", "<header><CRLF>\0", "<header><CRLF>\0", "error\0", "<header><CRLF>\0", "\0"},
     {"<field><field_>\0", "<field><field_>\0", "<field><field_>\0", "error\0", "\0", "\0"},
     {"error\0", "error\0", "error\0", "error\0", "<CRLF><record><record_>\0", "\0"},
     {"<field>\0", "\0", "<field>\0", "error\0", "\0", "error\0"},
     {"error\0", "<COMMA><name><name_>\0", "error\0", "error\0", "\0", "error\0"},
     {"<TEXT_>\0", "\0", "<DQUOTE><data><DQUOTE>\0", "error\0", "\0", "\0"},
     {"error\0", "<COMMA><field><field_>\0", "error\0", "error\0", "\0", "\0"},
     {"<TEXT><data>\0", "<COMMA><data>\0", "\0", "<DDQUOTE><data>\0", "<CRLF><data>\0", "error\0"},
     {"<TEXT><TEXT_>\0", "\0", "error\0", "error\0", "\0", "\0"},
     {"error\0", "error\0", "error\0", "error\0", "<CRLF><CRLF_>\0", "\0"}};

VAR_LIST *extract_var(const char *input)
{
    // printf("Inside extract_var:\n");
    int count = 0;
    VAR_LIST *head = NULL;

    VAR_LIST *temp = NULL;

    String *str = create_str();
    const char *ptr = input;

    if (*ptr == '<')
    {
        // printf("Inside if->%c\n", *ptr);
        append_char(str, *ptr);
        ptr++;
        while (*ptr != '>')
        {
            append_char(str, *ptr);
            (ptr)++;
        }
        append_char(str, *ptr);
        null_terminate(str);
        // printf("Inside if->%s\n", str->data);
        (ptr)++;
        // printf("Inside if->%c\n", *ptr);
        count++;
    }
    else
    {
        // printf("Inside else->%c\n", *ptr);
        (ptr)++;
    }

    head = (VAR_LIST *)malloc(sizeof(VAR_LIST));
    head->prev = NULL;
    head->str = str->data;
    head->next = NULL;

    str = NULL;
    str = create_str();

    while (*ptr != '\0')
    {
        // printf("Inside while loop->\n");
        if (*ptr == '<')
        {
            // printf("Inside if->%c\n", *ptr);
            append_char(str, *ptr);
            (ptr)++;
            while (*ptr != '>')
            {
                append_char(str, *ptr);
                (ptr)++;
            }
            append_char(str, *ptr);
            null_terminate(str);
            // printf("Inside if->%s\n", str->data);
            (ptr)++;
            // printf("Inside if->%c\n", *ptr);
            count++;
        }
        else
        {
            // printf("Inside else->%c\n", *ptr);
            (ptr)++;
        }
        if (count == 2)
        {
            temp = (VAR_LIST *)malloc(sizeof(VAR_LIST));
            temp->prev = head;
            temp->str = str->data;
            temp->next = NULL;
            head->next = temp;
        }
        else
        {
            temp->next = (VAR_LIST *)malloc(sizeof(VAR_LIST));
            temp->next->prev = temp;
            temp->next->str = str->data;
            temp->next->next = NULL;
            temp = temp->next;
        }
        str = NULL;
        str = create_str();
        // if (temp != NULL)
        //     printf("temp->%s\n", temp->str);
    }
    // printf("----End----\n");
    if (count == 1)
    {
        return head;
    }
    return temp;
}

int get_index(char *str)
{
    if (strcmp(str, "<file>") == 0)
        return 0;

    else if (strcmp(str, "<header>") == 0)
        return 1;

    else if (strcmp(str, "<header_>") == 0)
        return 2;

    else if (strcmp(str, "<record>") == 0)
        return 3;

    else if (strcmp(str, "<record_>") == 0)
        return 4;

    else if (strcmp(str, "<name>") == 0)
        return 5;

    else if (strcmp(str, "<name_>") == 0)
        return 6;

    else if (strcmp(str, "<field>") == 0)
        return 7;

    else if (strcmp(str, "<field_>") == 0)
        return 8;

    else if (strcmp(str, "<data>") == 0)
        return 9;

    else if (strcmp(str, "<TEXT_>") == 0)
        return 10;

    else if (strcmp(str, "<CRLF_>") == 0)
        return 11;

    return -1;
}

int parse(LIST *head)
{
    LIST *temp = head;
    push_str("$");
    push_str("<file>");
    while (!isempty_str() && temp != NULL)
    {
        char *s_top = peek_str();
        int type = temp->token->type;
        char *current_input = temp->token->value;
        if (type == TEXTDATA)
            current_input = "<TEXT>";
        if (type == COMMA)
            current_input = "<COMMA>";
        if (type == DQUOTE)
            current_input = "<DQUOTE>";
        if (type == DDQUOTE)
            current_input = "<DDQUOTE>";
        if (type == NEWLINE)
            current_input = "<CRLF>";

        if (strcmp(s_top, current_input) == 0)
        {
            pop_str();
            temp = temp->next;
        }
        else if (strcmp(current_input, "$") == 0 && get_index(s_top) == -1)
        {
            return 0;
        }
        else if (strcmp(LL1_TABLE[get_index(s_top)][type], "\0") == 0)
        {
            pop_str();
        }
        else if (strcmp(LL1_TABLE[get_index(s_top)][type], "error") == 0)
        {
            return 0;
        }
        else
        {
            VAR_LIST *production = extract_var(LL1_TABLE[get_index(s_top)][type]);
            pop_str();
            while (production != NULL)
            {
                push_str(production->str);
                production = production->prev;
            }
        }
        // STACK *t = S_TOP;
        // if (t == NULL)
        // {
        //     printf("NULL\n");
        // }
        // printf("S-------------\n");
        // while (t != NULL)
        // {
        //     printf("%s\n", t->value);
        //     t = t->next;
        // }
        // printf("E-------------\n");
    }
    if (isempty_str() && temp == NULL)
    {
        return 1;
    }
    return 0;
}