/*
 ** EPITECH PROJECT, 2024
** minishell
** File description:
** lexer header
*/

#ifndef MINISHELL2_LEXER_H
    #define MINISHELL2_LEXER_H
    #include <stddef.h>
typedef enum {
    TOKEN_END = 0,
    TOKEN_SEPARATOR,
    TOKEN_SYMBOL,
} token_kind_e;

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

#endif //MINISHELL2_LEXER_H
