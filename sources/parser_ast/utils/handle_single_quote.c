/*
** EPITECH PROJECT, 2024
** utils
** File description:
** handle_single_quote
*/

#include "lexer_ast.h"
#include <stdio.h>

int handle_single_quote(list_t *l, token_t *node)
{
    char *link_quote = &l->input[l->cursor];
    size_t n_cursor = 0;

    while (link_quote[n_cursor] != '\'' && link_quote[n_cursor] != '\0') {
        n_cursor += 1;
    }
    if (link_quote[n_cursor] == '\'') {
        return 0;
    } else {
        dprintf(2, "Unmatched '\''.\n");
        node->type = INVALID;
        return 84;
    }
    return 0;
}
