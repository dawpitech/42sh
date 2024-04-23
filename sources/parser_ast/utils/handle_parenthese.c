/*
** EPITECH PROJECT, 2024
** utils
** File description:
** handle_parenthese
*/

#include "lexer_ast.h"
#include <string.h>
#include <stdio.h>

static
int check_parenthese(list_t *l, token_t *node)
{
    if (l->input[l->cursor] == ')') {
        dprintf(2, "Too many )'s.\n");
        node->type = INVALID;
        return 84;
    }
    node->type = IDENTIFIER;
    l->cursor += 1;
    if (l->input[l->cursor] == ')') {
        dprintf(2, "Badly placed ()'s.\n");
        node->type = INVALID;
        return 84;
    }
    return 0;
}

int handle_parenthese(list_t *l, token_t *node)
{
    if (check_parenthese(l, node) == 84)
        return 84;
    node->text = strndup(&l->input[l->cursor], 1);
    while (l->input[l->cursor] != ')' && l->input[l->cursor] != '\0') {
        l->cursor += 1;
        if (l->input[l->cursor] != ')')
            node->text = strncat(node->text, &l->input[l->cursor], 1);
    }
    if (l->input[l->cursor] == ')') {
        l->cursor += 1;
    } else {
        dprintf(2, "Too many ('s.\n");
        node->type = INVALID;
        return 84;
    }
    return 0;
}
