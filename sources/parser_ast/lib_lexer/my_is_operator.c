/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_is_operator
*/

#include <stdio.h>
#include <string.h>
#include "lexer_ast.h"
#include "operator.h"
#include <stdlib.h>

int is_operator(list_t *list, token_t *node)
{
    for (int i = 0; LIST_OPERATOR[i] != '\0'; i ++)
        if (LIST_OPERATOR[i] == list->input[list->cursor]) {
            node->text = malloc(sizeof(char));
            node->type = OPERATOR;
            node->text = strndup(&list->input[list->cursor], 1);
            list->cursor += 1;
            return 1;
        }
    return 0;
}
