/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_isand
*/

#include "lexer_ast.h"
#include <stdlib.h>

int my_isand(list_t *list, token_t *node)
{
    if (list->cursor < list->input_len && list->input[list->cursor] == '&') {
        node->type = AND;
        node->text = strndup(&list->input[list->cursor], 1);
        list->cursor += 1;
        if (list->input[list->cursor] == '&') {
            node->type = D_AND;
            node->text = realloc(node->text, sizeof(char *) * 2);
            node->text = strncat(node->text, &list->input[list->cursor], 1);
            list->cursor += 1;
        }
        return 1;
    }
    return 0;
}
