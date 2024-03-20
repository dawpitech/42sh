/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** lexer header
*/

#ifndef MINISHELL2_LEXER_H
    #define MINISHELL2_LEXER_H
    #include <stddef.h>

#define IS_SPACE_CHARS_LEN (sizeof(ISSPACE_CHARS) / sizeof(char))

typedef enum {
    TOKEN_END = 0,
    TOKEN_SYMBOL,
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_REDIRECT_R,
    TOKEN_REDIRECT_L,
    TOKEN_REDIRECT_DOUBLE_R,
    TOKEN_REDIRECT_DOUBLE_L,
    TOKEN_INVALID,
} token_kind_e;

typedef struct {
    const char *text;
    token_kind_e kind;
} token_representation_t;

typedef struct {
    token_kind_e kind;
    const char *text;
    size_t text_len;
} token_t;

typedef struct {
    const char *content;
    size_t content_len;
    size_t cursor;
} lexer_t;

lexer_t lexer_new(const char *content, size_t content_len);
token_t lexer_next(lexer_t *l);
char *get_token_kind_as_str(token_kind_e kind);
void lexer_trim_ws_left(lexer_t *l);

#endif //MINISHELL2_LEXER_H
