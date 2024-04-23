/*
** EPITECH PROJECT, 2024
** parser
** File description:
** parser
*/

#include "lexer_ast.h"
#include "minishell.h"
#include "parser_ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

commands_t *parser_command(token_t **token)
{
    commands_t *command = malloc(sizeof(commands_t));

    if (!token || (*token)->type != IDENTIFIER || !command) {
        return NULL;
    }
    command->str = strdup((*token)->text);
    command->args = NULL;
    command->fd_in = STDIN_FILENO;
    command->fd_out = STDOUT_FILENO;
    while ((*token)->type == IDENTIFIER && (*token)->type != END) {
        command->args = realloc_args(command->args, (*token));
        (*token) = (*token)->next;
    }
    return command;
}

pipe_t *parser_pipe(token_t **token)
{
    pipe_t *new_pipe = NULL;

    if (!token)
        return NULL;
    new_pipe = init_pipe();
    new_pipe = fill_first_cmd_tab(new_pipe, token);
    if (new_pipe == NULL)
        return NULL;
    new_pipe = loop_pipe(new_pipe, token);
    if (new_pipe == NULL)
        return NULL;
    new_pipe = loop_redirect(new_pipe, token);
    new_pipe = loop_pipe(new_pipe, token);
    return new_pipe;
}

semicol_t *parser_semicol(token_t **token)
{
    semicol_t *new = NULL;

    if (!token) {
        return NULL;
    }
    new = init_semicol();
    if ((*token)->type != IDENTIFIER) {
        free(new);
        return NULL;
    }
    new = loop_semicol(new, token);
    return new;
}

or_t *parser_or(token_t **token)
{
    or_t *new = NULL;

    if (!token)
        return NULL;
    new = init_or();
    if ((*token)->type != IDENTIFIER ||
        ((*token)->type) != AND || (*token)->type != D_AND) {
        free(new); 
    }
    return new;
}

and_t *parser_and(token_t **token)
{
    and_t *new = NULL;

    if (!token)
        return NULL;
    new = init_and();
    if ((*token)->type != IDENTIFIER ||
        ((*token)->type) != AND || (*token)->type != D_AND) {
        free(new); 
    }
    return new;
}

int parse_input(shell_t *mysh)
{
    root_t *root = NULL;
    token_t *token = NULL;

    mysh->list = lexer(mysh, mysh->list);
    if (!mysh->list)
        return RET_ERROR;
    root = init_root();
    token = mysh->list->head;
    if (token->type != IDENTIFIER && token->type != SEMICOLOMN
        && token->type != AND && token->type != D_AND) {
        dprintf(2, "Invalid null command.\n");
        return RET_ERROR;
    }
    root = loop_root(root, &token);
    if (!root)
        return RET_ERROR;
    mysh->root = root;
    return RET_VALID;
}
