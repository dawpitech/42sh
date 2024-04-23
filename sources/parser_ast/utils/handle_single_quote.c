/*
** EPITECH PROJECT, 2024
** utils
** File description:
** handle_single_quote
*/

#include "lexer_ast.h"
#include <string.h>
#include <stdio.h>

int handle_single_quote(list_t *l, token_t *node)
{
    node->type = IDENTIFIER;
    l->cursor += 1;
    node->text = strndup(&l->input[l->cursor], 1);
    while (l->input[l->cursor] != '\'' && l->input[l->cursor] != '\0') {
        l->cursor += 1;
        node->text = strncat(node->text, &l->input[l->cursor], 1);
    }
    if (l->input[l->cursor] == '\'') {
        l->cursor += 1;
    } else {
        dprintf(2, "Unmatched '\''.\n");
        node->type = INVALID;
        return 84;
    }
    return 0;
}
