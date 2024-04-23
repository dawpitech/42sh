/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_right_redirect
*/

#include "lexer_ast.h"

int my_isredirect_file_to_command(list_t *list, token_t *node)
{
    if (list->input[list->cursor] == '<') {
        node->type = IN;
        node->text = strndup(&list->input[list->cursor], 1);
        list->cursor += 1;
        if (list->input[list->cursor] == '<') {
            node->type = D_IN;
            node->text = strncat(node->text, &list->input[list->cursor], 1);
            list->cursor += 1;
        }
        return 1;
    }
    return 0;
}
