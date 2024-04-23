/*
** EPITECH PROJECT, 2024
** header lexer
** File description:
** lexer
*/

#ifndef LEXER_H
    #define LEXER_H

    #include <string.h>

    #define LIST_OPERATOR ("\'()\n\"")

typedef enum { IDENTIFIER, OPERATOR,
    PIPE,
    OR,
    AND,
    D_AND,
    SEMICOLOMN,
    OUT, // >
    D_OUT, // >>
    IN, // <
    D_IN, // <<
    INVALID,
    END,
} token_type;

typedef struct token_s {
    token_type type;
    char *text;
    struct token_s *next;
} token_t;

typedef struct list_s {
    char *input;
    size_t cursor;
    size_t input_len;
    token_t *head;
} list_t;

list_t *init_list(list_t *new, char *input);
void free_lexer_list(list_t *list);

int my_isdigit(char c);
int my_isand(list_t *list, token_t *node);
int my_ispipe(list_t *list, token_t *node);
int my_issemicol(list_t *list, token_t *node);
int my_isspace(char c);
int is_operator(list_t *list, token_t *node);
int my_isredirect_command_to_file(list_t *list, token_t *node);
int my_isredirect_file_to_command(list_t *list, token_t *node);
int my_isalphanum(list_t *list, token_t *node);
int my_list_len(list_t *list);
int my_isalpha_lexer(char const c);

#endif /* LEXER_H */
