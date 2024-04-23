/*
** EPITECH PROJECT, 2024
** include
** File description:
** operator
*/

#ifndef OPERATOR_H 
    #define OPERATOR_H

    #include <stddef.h>
    #include "lexer_ast.h"

typedef struct operator_s {
    char open;
    int (*execute_func)(list_t *list, token_t *node);
} operator_t;

int handle_single_quote(list_t *list, token_t *node);
int handle_double_quote(list_t *l, token_t *node);
int handle_parenthese(list_t *l, token_t *node);

operator_t tab_operator[] = {
    {'\'', &handle_single_quote},
    {'\"', &handle_double_quote},
    {'(', &handle_parenthese},
    {')', &handle_parenthese},
    {0, 0, NULL}
};

#endif /* OPERATOR_H */
