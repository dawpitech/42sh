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
int realloc_tab_or(and_t *and_obj)
{
    if (!and_obj)
        return RET_ERROR;
    if (and_obj->size == 0)
        and_obj->tab_or = malloc(sizeof(or_t *) * 2);
    else
        and_obj->tab_or = realloc(and_obj->tab_or, sizeof(or_t *) *
            (and_obj->size + 2));
    if (!and_obj->tab_or)
        return RET_ERROR;
    and_obj->tab_or[and_obj->size + 1] = NULL;
    return RET_VALID;
}

and_t *loop_and(and_t *and_obj, token_t **token, shell_t *shell)
{
    while ((*token) && ((*token)->type == IDENTIFIER ||
        (*token)->type == D_AND || (*token)->type == AND ||
        (*token)->type == OPERATOR ||
        (*token)->type == L_PAREN || (*token)->type == R_PAREN)) {
        if (realloc_tab_or(and_obj) == RET_ERROR) {
            free(and_obj);
            return NULL;
        }
        and_obj->tab_or[and_obj->size] = parser_or(token, shell);
        and_obj->size += 1;
        if (!and_obj || !and_obj->tab_or[and_obj->size - 1]) {
            free(and_obj);
            return NULL;
        }
        if ((*token) == NULL || (*token)->type != D_AND)
            break;
        if ((*token)->next != NULL)
            (*token) = (*token)->next;
    }
    return and_obj;
}
