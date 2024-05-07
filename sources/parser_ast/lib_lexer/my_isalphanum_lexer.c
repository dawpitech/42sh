/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_isalphanum_lexer
*/

#include "lexer_ast.h"
#include <ctype.h>
#include <stdlib.h>

int my_isalphanum(list_t *l, token_t *node)
{
    if (isdigit(l->input[l->cursor]) ||
        my_isalpha_lexer(l->input[l->cursor]) == 0 ||
        l->input[l->cursor] == '_' ||
        l->input[l->cursor] == '-' ||
        l->input[l->cursor] == '~' || l->input[l->cursor] == '!') {
        node->type = IDENTIFIER;
        node->text = strndup(&l->input[l->cursor], 1);
        l->cursor += 1;
        while (isdigit(l->input[l->cursor]) ||
            my_isalpha_lexer(l->input[l->cursor]) == 0 ||
            l->input[l->cursor] == '_' ||
            l->input[l->cursor] == '-' ||
            l->input[l->cursor] == '~' || l->input[l->cursor] == '!') {
            node->text = realloc(node->text, strlen(node->text) + 2);
            node->text = strncat(node->text, &l->input[l->cursor], 1);
            l->cursor += 1;
        }
        return 1;
    }
    return 0;
}
