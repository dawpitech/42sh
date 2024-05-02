/*
** EPITECH PROJECT, 2024
** utils
** File description:
** handle_single_quote
*/

#include <string.h>
#include <stdlib.h>
#include "lexer_ast.h"

static
char *quoted_string_loop(char *str_quoted, token_t **token, char *op)
{
    while (strcmp((*token)->text, op) != 0 && (*token)->type != END) {
        str_quoted = realloc(str_quoted,
            sizeof(char) * (strlen(str_quoted) + strlen((*token)->text) + 2));
        str_quoted = strcat(str_quoted, " ");
        str_quoted = strcat(str_quoted, (*token)->text);
        (*token) = (*token)->next;
    }
    return str_quoted;
}

char *handle_operator(token_t **token)
{
    char *str_quoted = NULL;
    char *op = NULL;

    if ((*token)->type != OPERATOR)
        return strdup((*token)->text);
    if (strcmp((*token)->text, "!") == 0)
        return strdup((*token)->text);
    op = (*token)->text;
    (*token) = (*token)->next;
    if (strcmp("\"", op) != 0 && strcmp("\'", op) != 0)
        return NULL;
    if ((*token)->type != END && strcmp((*token)->text, op) != 0)
        str_quoted = strdup((*token)->text);
    (*token) = (*token)->next;
    str_quoted = quoted_string_loop(str_quoted, token, op);
    if ((*token)->type != OPERATOR)
        return NULL;
    return str_quoted;
}
