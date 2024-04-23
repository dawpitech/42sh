/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_ispipe
*/

#include "lexer_ast.h"

int my_ispipe(list_t *list, token_t *node)
{
    if (list->input[list->cursor] == '|') {
        node->type = PIPE;
        node->text = strndup(&list->input[list->cursor], 1);
        list->cursor += 1;
        if (list->input[list->cursor] == '|') {
            node->type = OR;
            node->text = strncat(node->text, &list->input[list->cursor], 1);
            list->cursor += 1;
        }
        return 1;
    }
    return 0;
}
