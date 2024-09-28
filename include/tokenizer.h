#ifndef TOKENIZER
#define TOKENIZER

enum Identifier
{
    TEXTDATA,
    COMMA,
    DQUOTE,
    DDQUOTE,
    NEWLINE,
    DOLLAR
};

typedef struct Token
{
    char *value;
    int type;
} Token;

typedef struct TOKEN_LIST
{
    Token *token;
    struct TOKEN_LIST *next;
} LIST;

// Make a token
Token *make_token(char *str, int type);

// Check id state and return that str
Token *move(char **ptr);

// tokenize input
LIST *tokenize(char **input);

// Traverse list
void traverse_list(LIST *head);

// Extract text data
char *extract_text(char **ptr);

#endif