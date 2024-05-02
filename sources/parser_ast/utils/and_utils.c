/*
** EPITECH PROJECT, 2024
** utils
** File description:
** and_utils
*/

#include "lexer_ast.h"
#include "minishell.h"
#include <stdlib.h>

static
int realloc_tab_or(and_t *and)
{
    if (!and)
        return RET_ERROR;
    if (and->size == 0)
        and->tab_or = malloc(sizeof(or_t *) * 2);
    else
        and->tab_or = realloc(and->tab_or, sizeof(or_t *) * (and->size + 2));
    and->tab_or[and->size] = malloc(sizeof(or_t));
    if (!and->tab_or || !and->tab_or[and->size])
        return RET_ERROR;
    and->tab_or[and->size + 1] = NULL;
    return RET_VALID;
}

and_t *loop_and(and_t *and, token_t **token, shell_t *shell)
{
    while ((*token) && ((*token)->type == IDENTIFIER ||
        (*token)->type == D_AND || (*token)->type == AND ||
        (*token)->type == OPERATOR ||
        (*token)->type == L_PAREN || (*token)->type == R_PAREN)) {
        if (realloc_tab_or(and) == RET_ERROR) {
            free(and);
            return NULL;
        }
        and->tab_or[and->size] = parser_or(token, shell);
        and->size += 1;
        if (!and || !and->tab_or[and->size - 1]) {
            free(and);
            return NULL;
        }
        if ((*token) == NULL || (*token)->type != D_AND)
            break;
        if ((*token)->next != NULL)
            (*token) = (*token)->next;
    }
    return and;
}
