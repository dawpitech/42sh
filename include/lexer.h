/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** lexer header
*/

#ifndef MINISHELL2_LEXER_H
    #define MINISHELL2_LEXER_H
    #include <stddef.h>
    #include "minishell.h"
typedef enum {
    TOKEN_END = 0,
    TOKEN_SYMBOL,
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_REDIRECT_R,
    TOKEN_REDIRECT_L,
    TOKEN_REDIRECT_RR,
    TOKEN_REDIRECT_LL,
    TOKEN_INVALID,
} token_kind_t;

typedef struct {
    const char *text;
    token_kind_t kind;
} token_representation_t;

typedef struct {
    token_kind_t kind;
    const char *text;
    size_t text_len;
} token_t;

typedef struct {
    const char *content;
    size_t content_len;
    size_t cursor;
    bool is_in_command;
    cmd_t current_cmd;
} lexer_t;

lexer_t lexer_new(const char *content, size_t content_len);
token_t lexer_next(lexer_t *l);
char *get_token_kind_as_str(token_kind_t kind);
void lexer_trim_ws_left(lexer_t *l);

#endif //MINISHELL2_LEXER_H
