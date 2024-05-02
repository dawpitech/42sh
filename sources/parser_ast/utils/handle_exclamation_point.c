/*
** EPITECH PROJECT, 2024
** utils
** File description:
** handle_exclamation_point
*/

#include "lexer_ast.h"
#include "minishell.h"
#include "lexer_ast.h"
#include <string.h>

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int handle_exclamation_point(pipe_t *pipe, shell_t *shell, token_t **token,
    int idx)
{
    commands_t *c = NULL; 

    if ((*token)->type != OPERATOR || strcmp((*token)->text, "!") != 0)
        return 84;
    c = malloc(sizeof(commands_t));
    c->exec_name = strdup((*token)->text);
    c->argv = malloc(sizeof(char *) * 2);
    c->argv[0] = strdup(c->exec_name);
    c->argv[1] = NULL;
    c->argc = 1;
    c->fd_in = STDIN_FILENO;
    c->fd_out = STDOUT_FILENO;
    c->shell = shell;
    (*token) = (*token)->next;
    fill_arguments(token, c);
    pipe->tab_command[idx] = c;
    pipe->size += 1;
    return RET_VALID;
}
