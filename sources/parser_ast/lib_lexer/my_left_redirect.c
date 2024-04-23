/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_left_redirect
*/

#include "lexer_ast.h"

int my_isredirect_command_to_file(list_t *list, token_t *node)
{
    if (list->input[list->cursor] == '>') {
        node->type = OUT;
        node->text = strndup(&list->input[list->cursor], 1);
        list->cursor += 1;
        if (list->input[list->cursor] == '>') {
            node->type = D_OUT;
            node->text = strncat(node->text, &list->input[list->cursor], 1);
            list->cursor += 1;
        }
        return 1;
    }
    return 0;
}
