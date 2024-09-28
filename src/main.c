#include "tokenizer.h"
#include "csv_file_reader.h"
#include "csv_string.h"
#include "parser.h"
#include <stdio.h>

int main()
{
    printf("CSV Parser!\n");
    // char *student = "\"Akash Kumar\r\nAP\",23,MCA\r\n\0";
    // printf("%s", student);
    // tokenize(&student);

    // char *str = "\r\0";
    // printf("%c", str[0]);
    // printf("Hi");

    FILE *ptr = open_csv("../ap.csv");
    String *str = get_one_line(ptr);
    LIST *head = tokenize(&str->data);
    traverse_list(head);
    printf("%d\n", parse(head));

    str = get_one_line(ptr);
    head = tokenize(&str->data);
    traverse_list(head);
    printf("%d\n", parse(head));

    str = get_one_line(ptr);
    head = tokenize(&str->data);
    traverse_list(head);
    printf("%d\n", parse(head));

    str = get_one_line(ptr);
    head = tokenize(&str->data);
    traverse_list(head);
    printf("%d\n", parse(head));

    return 0;
}