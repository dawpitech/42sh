/*
** EPITECH PROJECT, 2024
** utils
** File description:
** handle_single_quote
*/

#include <string.h>

#include "lexer_ast.h"
#include "parser_ast.h"

char *handle_operator(token_t **token)
{
    char *str_quoted = NULL;
    char *op = NULL;

    if ((*token)->type != OPERATOR)
        return strdup((*token)->text);
    op = (*token)->text;
    (*token) = (*token)->next;
    if (strcmp("\"", op) != 0 && strcmp("\'", op) != 0)
        return NULL;
    if ((*token)->type != END)
        str_quoted = strdup((*token)->text);
    while (strcmp((*token)->text, op) != 0 && (*token)->type != END) {
        str_quoted = strcat(str_quoted, " ");
        str_quoted = strcat(str_quoted, (*token)->text);
        (*token) = (*token)->next;
    }
    if ((*token)->type != OPERATOR)
        return NULL;
    return str_quoted;
}
