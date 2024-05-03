/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_issemicol
*/

#include "lexer_ast.h"

int my_issemicol(list_t *list, token_t *node)
{
    if (list->input[list->cursor] == ';') {
        node->type = SEMICOLOMN;
        node->text = strndup(&list->input[list->cursor], 1);
        list->cursor += 1;
        return 1;
    }
    return 0;
}
