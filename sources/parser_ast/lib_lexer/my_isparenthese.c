/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_isparenthese
*/

#include "lexer_ast.h"

int my_isparenthese(list_t *list, token_t *node)
{
    if (list->input[list->cursor] == '(') {
        node->type = L_PAREN;
        node->text = strndup(&list->input[list->cursor], 1);
        list->cursor += 1;
        return 1;
    }
    if (list->input[list->cursor] == ')') {
        node->type = R_PAREN;
        node->text = strndup(&list->input[list->cursor], 1);
        list->cursor += 1;
        return 1;
    }
    return 0;
}
