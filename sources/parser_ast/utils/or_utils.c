/*
** EPITECH PROJECT, 2024
** utils
** File description:
** or_utils
*/

#include <stdlib.h>

#include "lexer_ast.h"
#include "minishell.h"

int realloc_tab_pipe(or_t *or)
{
    if (!or)
        return RET_ERROR;
    if (or->size == 0)
        or->tab_pipe = malloc(sizeof(pipe_t *) * 2);
    else
        or->tab_pipe = realloc(or->tab_pipe,
            sizeof(pipe_t *) * (or->size + 2));
    or->tab_pipe[or->size] = malloc(sizeof(pipe_t));
    if (!or || !or->tab_pipe[or->size])
        return RET_ERROR;
    or->tab_pipe[or->size + 1] = NULL;
    return RET_VALID;
}

or_t *loop_or(or_t *or, token_t **token, shell_t *shell)
{
    while ((*token) && ((*token)->type == IDENTIFIER ||
        (*token)->type == OPERATOR ||
        (*token)->type == L_PAREN || (*token)->type == R_PAREN)) {
        if (realloc_tab_pipe(or) == RET_ERROR) {
            free(or);
            return NULL;
        }
        or->tab_pipe[or->size] = parser_pipe(token, shell);
        or->size += 1;
        if (!or || !or->tab_pipe[or->size - 1]) {
            free(or);
            return NULL;
        }
        if ((*token) == NULL || (*token)->type != OR) {
            break;
        }
        if ((*token)->next != NULL)
            (*token) = (*token)->next;
    }
    return or;
}
