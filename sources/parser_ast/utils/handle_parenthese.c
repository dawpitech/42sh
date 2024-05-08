/*
** EPITECH PROJECT, 2024
** utils
** File description:
** handle_parenthese
*/

#include <stdlib.h>
#include <string.h>

#include "lexer_ast.h"
#include "minishell.h"

int handle_parenthese(pipe_t *pipe, token_t **token, shell_t *shell)
{
    char *str = NULL;

    if ((*token)->type != L_PAREN)
        return RET_VALID;
    (*token) = (*token)->next;
    str = strdup((*token)->text);
    (*token) = (*token)->next;
    while ((*token)->type != R_PAREN) {
        str = realloc(str,
            sizeof(char) * (strlen(str) + strlen((*token)->text) + 2));
        str = strcat(str, " ");
        str = strcat(str, (*token)->text);
        (*token) = (*token)->next;
    }
    pipe->tab_command[pipe->size]->sub_shell = parse_input(str, shell);
    (*token) = (*token)->next;
    if (!pipe->tab_command[pipe->size]->sub_shell)
        return RET_ERROR;
    pipe->size ++;
    return RET_VALID;
}
