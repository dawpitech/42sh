/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_isalphanum_lexer
*/

#include "lexer_ast.h"
#include <ctype.h>
#include <stdlib.h>

int my_isalphanum(list_t *list, token_t *node)
{
    if (isdigit(list->input[list->cursor]) == 1 ||
        my_isalpha_lexer(list->input[list->cursor]) == 0 ||
        list->input[list->cursor] == '_' ||
        list->input[list->cursor] == '-' ||
        list->input[list->cursor] == '~') {
        node->type = IDENTIFIER;
        node->text = strndup(&list->input[list->cursor], 1);
        list->cursor += 1;
        while (isdigit(list->input[list->cursor]) == 1 ||
            my_isalpha_lexer(list->input[list->cursor]) == 0 ||
            list->input[list->cursor] == '_' ||
            list->input[list->cursor] == '-' ||
            list->input[list->cursor] == '~') {
            node->text = realloc(node->text, strlen(node->text) + 2);
            node->text = strncat(node->text, &list->input[list->cursor], 1);
            list->cursor += 1;
        }
        return 1;
    }
    return 0;
}
