/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** lexer
*/

#include <stdbool.h>
#include <stdlib.h>

#include "lexer.h"
#include "my.h"

const token_representation_t token_repr[] = {
    {.text = "|", .kind = TOKEN_PIPE},
    {.text = ";", .kind = TOKEN_SEMICOLON},
    {.text = ">", .kind = TOKEN_REDIRECT_R},
    {.text = "<", .kind = TOKEN_REDIRECT_L},
    {.text = ">>", .kind = TOKEN_REDIRECT_DOUBLE_R},
    {.text = "<<", .kind = TOKEN_REDIRECT_DOUBLE_L},
};

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
    static const char SPECIALS_CHARS[] = {'|', ';', '>', '<', '\'', '\"', ' ', 0};
    static const size_t S_CHARS_LEN = sizeof(SPECIALS_CHARS) / sizeof(char);

    for (size_t i = 0; i < S_CHARS_LEN; i += 1) {
        if (chr == SPECIALS_CHARS[i])
            return true;
    }
    return false;
}

static
bool token_start_withs(lexer_t *l, char const *prefix)
{
    size_t prefix_len = my_strlen(prefix);

    if (prefix_len == 0)
        return true;
    if (l->cursor + prefix_len >= l->content_len)
        return false;
    my_strncmp(prefix, l->content, prefix_len);
}

char *get_token_kind_as_str(token_kind_e kind)
{
    switch (kind) {
        case TOKEN_END:
            return "end token";
        case TOKEN_SYMBOL:
            return "symbol";
        case TOKEN_PIPE:
            return "pipe";
        case TOKEN_SEMICOLON:
            return "semicolon";
        case TOKEN_REDIRECT_R:
            return "right redirect";
        case TOKEN_REDIRECT_L:
            return "left redirect";
        case TOKEN_REDIRECT_DOUBLE_R:
            return "double right redirect";
        case TOKEN_REDIRECT_DOUBLE_L:
            return "double left redirect";
        case TOKEN_INVALID:
            return "invalid token";
        default:
            exit(69);
    }
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

token_t lexer_next(lexer_t *l)
{
    token_t token = {0};

    lexer_trim_ws_left(l);
    token.text = &(l->content[l->cursor]);

    if (l->cursor >= l->content_len)
        return token;

    if (l->content[l->cursor] == '\"') {
        token.kind = TOKEN_SYMBOL;
        l->cursor += 1;
        token.text += 1;
        while (l->content[l->cursor] != '\"' && l->content[l->cursor] != '\0') {
            l->cursor += 1;
            token.text_len += 1;
        }
        if (l->content[l->cursor] == '\"') {
            l->cursor += 1;
        } else {
            my_put_stderr("Unmatched '\"'.\n");
            token.kind = TOKEN_INVALID;
        }
        return token;
    }

    if (l->content[l->cursor] == ';') {
        l->cursor += 1;
        token.kind = TOKEN_SEMICOLON;
        token.text_len = 1;
        return token;
    }

    if (!is_special_char(l->content[l->cursor])) {
        token.kind = TOKEN_SYMBOL;
        while (!is_special_char(l->content[l->cursor])) {
            l->cursor += 1;
            token.text_len += 1;
        }
        return token;
    }

    token.kind = TOKEN_INVALID;
    token.text_len = 1;
    l->cursor += 1;
    return token;
}
