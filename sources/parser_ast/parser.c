/*
** EPITECH PROJECT, 2024
** parser
** File description:
** parser
*/

#include <stdio.h>
#include <string.h>

#include "lexer_ast.h"
#include "minishell.h"

pipe_t *parser_pipe(token_t **token, shell_t *shell)
{
    pipe_t *new_pipe = NULL;

    if (!token)
        return NULL;
    new_pipe = init_pipe();
    new_pipe = loop_pipe(new_pipe, token, shell);
    return new_pipe;
}

or_t *parser_or(token_t **token, shell_t *shell)
{
    or_t *new = NULL;

    if ((*token)->type != IDENTIFIER && (*token)->type != OPERATOR
        && (*token)->type != AND && (*token)->type != L_PAREN)
        return NULL;
    new = init_or();
    new = loop_or(new, token, shell);
    return new;
}

and_t *parser_and(token_t **token, shell_t *shell)
{
    and_t *new = NULL;

    if ((*token)->type != IDENTIFIER && ((*token)->type) != AND &&
        (*token)->type != OPERATOR && (*token)->type != D_AND
        && (*token)->type != L_PAREN) {
        return NULL;
    }
    new = init_and();
    new = loop_and(new, token, shell);
    return new;
}

semicol_t *parser_semicol(token_t **token, shell_t *shell)
{
    semicol_t *new = NULL;

    if ((*token)->type != IDENTIFIER && ((*token)->type) != AND
        && (*token)->type != D_AND && (*token)->type != OPERATOR
        && (*token)->type != L_PAREN) {
        return NULL;
    }
    new = init_semicol();
    new = loop_semicol(new, token, shell);
    return new;
}

static
int check_first_type(token_t *token)
{
    if (token->type != IDENTIFIER && token->type != SEMICOLOMN
        && token->type != AND && token->type != D_AND &&
        token->type != OPERATOR && token->type != L_PAREN
        && token->type != R_PAREN) {
        dprintf(2, "Invalid null command.\n");
        return RET_ERROR;
    }
    return RET_VALID;
}

root_t *parse_input(char *raw_input, shell_t *shell)
{
    root_t *root = NULL;
    token_t *token = NULL;
    list_t *list = NULL;

    list = lexer(raw_input, list);
    if (list)
        if (backtrack_lexer(list->head) == RET_ERROR)
            return NULL;
    if (!list)
        return NULL;
    root = init_root();
    token = list->head;
    if (check_first_type(token) == RET_ERROR)
        return NULL;
    root = loop_root(root, &token, shell);
    free_lexer_list(list);
    if (!root)
        return NULL;
    return root;
}
