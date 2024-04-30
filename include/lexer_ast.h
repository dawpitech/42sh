/*
** EPITECH PROJECT, 2024
** header lexer
** File description:
** lexer
*/

#ifndef LEXER_H
    #define LEXER_H

    #include <string.h>
    #include <stdbool.h>

    #define LIST_OPERATOR ("\'\n\"")

typedef enum token_type_s {
    IDENTIFIER,
    OPERATOR,
    PIPE, // |
    OR, // ||
    AND, // &
    D_AND, // &&
    SEMICOLOMN, // ;
    L_PAREN, // (
    R_PAREN, // )
    OUT, // >
    D_OUT, // >>
    IN, // <
    D_IN, // <<
    INVALID, // x
    END, // '\0'
} token_type_t;

typedef struct backtrack_s {
    bool is_dquote;
    bool is_squote;
    bool error_l_paren;
    bool error_r_paren;
    bool error_badly_placed_d;
    bool error_badly_placed_s;
    bool error_invalid;
    int count_dquote;
    int count_squote;
    int loop_count;
    int count_paren;
} backtrack_t;

typedef struct token_s {
    token_type_t type;
    char *text;
    struct token_s *next;
} token_t;

typedef struct list_s {
    char *input;
    size_t cursor;
    size_t input_len;
    token_t *head;
} list_t;

list_t *lexer(char *raw_input, list_t *list);
list_t *init_list(list_t *new, char *input);
void free_lexer_list(list_t *list);
int backtrack_lexer(token_t *token);

// OPERATOR
int is_operator(list_t *list, token_t *node);
int handle_double_quote(list_t *l, token_t *node);
int handle_single_quote(list_t *l, token_t *node);
char *handle_operator(token_t **token);

int my_isparenthese(list_t *list, token_t *node);
int my_isdigit(char c);
int my_isand(list_t *list, token_t *node);
int my_ispipe(list_t *list, token_t *node);
int my_issemicol(list_t *list, token_t *node);
int my_isspace(char c);
int is_redirection(list_t *list, token_t *node);
int my_isalphanum(list_t *list, token_t *node);
int my_list_len(list_t *list);
int my_isalpha_lexer(char const c);

#endif /* LEXER_H */
