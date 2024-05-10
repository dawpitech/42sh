/*
** EPITECH PROJECT, 2024
** utils
** File description:
** or_utils
*/

#include <stdlib.h>

#include "lexer_ast.h"
#include "minishell.h"

int realloc_tab_pipe(or_t *or_obj)
{
    if (!or_obj)
        return RET_ERROR;
    if (or_obj->size == 0)
        or_obj->tab_pipe = malloc(sizeof(pipe_t *) * 2);
    else
        or_obj->tab_pipe = realloc(or_obj->tab_pipe,
            sizeof(pipe_t *) * (or_obj->size + 1));
    if (!or_obj)
        return RET_ERROR;
    or_obj->tab_pipe[or_obj->size + 1] = NULL;
    return RET_VALID;
}

or_t *loop_or(or_t *or_obj, token_t **token, shell_t *shell)
{
    while ((*token) && ((*token)->type == IDENTIFIER ||
        (*token)->type == OPERATOR ||
        (*token)->type == L_PAREN || (*token)->type == R_PAREN)) {
        if (realloc_tab_pipe(or_obj) == RET_ERROR) {
            free(or_obj);
            return NULL;
        }
        or_obj->tab_pipe[or_obj->size] = parser_pipe(token, shell);
        or_obj->size += 1;
        if (!or_obj || !or_obj->tab_pipe[or_obj->size - 1]) {
            free(or_obj);
            return NULL;
        }
        if ((*token) == NULL || (*token)->type != OR) {
            break;
        }
        if ((*token)->next != NULL)
            (*token) = (*token)->next;
    }
    return or_obj;
}
