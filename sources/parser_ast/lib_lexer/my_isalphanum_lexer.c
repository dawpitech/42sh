/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_isalphanum_lexer
*/

#include "lexer_ast.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

static
char *backtick_getline(list_t *l, token_t *node)
{
    char *input = NULL;
    size_t len = 0;

    dprintf(1, "? ");
    if (getline(&input, &len, stdin) == -1) {
        return NULL;
    }
    if (!node->text) {
        node->text = strndup(input, strlen(input) - 1);
    } else {
        node->text = realloc(node->text,
            sizeof(char) * (strlen(input) + strlen(node->text) + 2));
        node->text = strncat(node->text, input, strlen(input) - 1);
    }
    l->cursor += 1;
    return node->text;
}

static
char *handle_backtick(list_t *l, token_t *node)
{
    if (l->input[l->cursor] != '\\')
        return NULL;
    l->cursor += 1;
    if (l->cursor == l->input_len) {
        return backtick_getline(l, node);
    }
    if (!node->text)
        node->text = strndup(&l->input[l->cursor], 1);
    else {
        node->text = realloc(node->text,
            sizeof(char) * (strlen(node->text) + 3));
        node->text = strncat(node->text, &l->input[l->cursor], 1);
    }
    return node->text;
}

static
char *add_to_str(list_t *l, token_t *node)
{
    while (isdigit(l->input[l->cursor]) ||
        my_isalpha_lexer(l->input[l->cursor]) == 0 ||
        l->input[l->cursor] == '_' ||
        l->input[l->cursor] == '-' ||
        l->input[l->cursor] == '~' || l->input[l->cursor] == '!' ||
        l->input[l->cursor] == '\\') {
        if (l->input[l->cursor] == '\\') {
            node->text = handle_backtick(l, node);
        } else {
            node->text = realloc(node->text, strlen(node->text) + 2);
            node->text = strncat(node->text, &l->input[l->cursor], 1);
            l->cursor += 1;
        }
    }
    return node->text;
}

int my_isalphanum(list_t *l, token_t *node)
{
    if (isdigit(l->input[l->cursor]) ||
        my_isalpha_lexer(l->input[l->cursor]) == 0 ||
        l->input[l->cursor] == '_' ||
        l->input[l->cursor] == '-' ||
        l->input[l->cursor] == '~' || l->input[l->cursor] == '!'
        || l->input[l->cursor] == '\\') {
        node->type = IDENTIFIER;
        if (l->input[l->cursor] == '\\')
            node->text = handle_backtick(l, node);
        else
            node->text = strndup(&l->input[l->cursor], 1);
        l->cursor += 1;
        if (l->cursor < l->input_len)
            node->text = add_to_str(l, node);
        return 1;
    }
    return 0;
}
