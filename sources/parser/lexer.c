/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** lexer
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "my.h"

static
bool my_isspace(char chr)
{
    static const char SPACE_CHARS[] = {'\t', '\n', '\v', '\f', '\r', ' '};
    static const size_t S_CHARS_LEN = sizeof(SPACE_CHARS) / sizeof(char);

    for (size_t i = 0; i < S_CHARS_LEN; i += 1) {
        if (chr == SPACE_CHARS[i])
            return true;
    }
    return false;
}

static
bool is_special_char(char chr)
{
    static const char SPECIALS_CHARS[] = {'|', ';', '>',
        '<', '\'', '\"', '&', 0};
    static const size_t S_CHARS_LEN = sizeof(SPECIALS_CHARS) / sizeof(char);

    for (size_t i = 0; i < S_CHARS_LEN; i += 1) {
        if (chr == SPECIALS_CHARS[i] || my_isspace(chr))
            return true;
    }
    return false;
}

lexer_t lexer_new(char const *content, size_t content_len)
{
    lexer_t l = {0};

    l.content = content;
    l.content_len = content_len;
    return l;
}

void lexer_trim_ws_left(lexer_t *l)
{
    while (l->cursor < l->content_len && my_isspace(l->content[l->cursor])) {
        l->cursor += 1;
    }
}

static
token_t handle_double_quotes(lexer_t *l, token_t *token)
{
    token->kind = TOKEN_SYMBOL;
    l->cursor += 1;
    token->text += 1;
    while (l->content[l->cursor] != '\"' && l->content[l->cursor] != '\0') {
        l->cursor += 1;
        token->text_len += 1;
    }
    if (l->content[l->cursor] == '\"') {
        l->cursor += 1;
    } else {
        my_put_stderr("Unmatched '\"'.\n");
        token->kind = TOKEN_INVALID;
    }
    return *token;
}

static
token_t handle_semicolon(lexer_t *l, token_t *token)
{
    token->kind = TOKEN_SEMICOLON;
    token->text_len = 1;
    l->cursor += 1;
    return *token;
}

static
token_t handle_symbols(lexer_t *l, token_t *token)
{
    token->kind = TOKEN_SYMBOL;
    while (!is_special_char(l->content[l->cursor])) {
        l->cursor += 1;
        token->text_len += 1;
    }
    return *token;
}

static
void search_literals(lexer_t *l, token_t *token)
{
    if (my_strncmp(">>", &(l->content[l->cursor]), 2) == 0)
        token->kind = TOKEN_REDIRECT_RR;
    if (my_strncmp("<<", &(l->content[l->cursor]), 2) == 0)
        token->kind = TOKEN_REDIRECT_LL;
    if (my_strncmp("||", &(l->content[l->cursor]), 2) == 0)
        token->kind = TOKEN_OR;
    if (my_strncmp("&&", &(l->content[l->cursor]), 2) == 0)
        token->kind = TOKEN_AND;
    if (token->kind != TOKEN_END) {
        token->text_len += 2;
        l->cursor += 2;
        return;
    }
    if (my_strncmp(">", &(l->content[l->cursor]), 1) == 0)
        token->kind = TOKEN_REDIRECT_R;
    if (my_strncmp("<", &(l->content[l->cursor]), 1) == 0)
        token->kind = TOKEN_REDIRECT_L;
    if (my_strncmp("|", &(l->content[l->cursor]), 1) == 0)
        token->kind = TOKEN_PIPE;
    token->text_len += 1;
    l->cursor += 1;
}

token_t lexer_next(lexer_t *l)
{
    token_t token = {0};

    lexer_trim_ws_left(l);
    token.text = &(l->content[l->cursor]);
    if (l->cursor >= l->content_len)
        return token;
    if (l->content[l->cursor] == '\"')
        return handle_double_quotes(l, &token);
    if (l->content[l->cursor] == ';')
        return handle_semicolon(l, &token);
    if (!is_special_char(l->content[l->cursor]))
        return handle_symbols(l, &token);
    search_literals(l, &token);
    if (token.kind == TOKEN_END) {
        token.kind = TOKEN_INVALID;
        token.text_len = 1;
        l->cursor += 1;
    }
    return token;
}
