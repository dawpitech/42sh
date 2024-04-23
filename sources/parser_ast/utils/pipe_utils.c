/*
** EPITECH PROJECT, 2024
** utils
** File description:
** pipe_utils
*/

#include "minishell.h"
#include "my.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser_ast.h"
#include "lexer_ast.h"

int init_fd(pipe_t *s_pipe)
{
    int fd[2] = {0};

    if (pipe(fd) == -1) {
        return RET_ERROR;
    }
    s_pipe->tab_command[s_pipe->size]->fd_in = fd[0];
    s_pipe->tab_command[s_pipe->size - 1]->fd_out = fd[1];
    return RET_VALID;
}

pipe_t *fill_first_cmd_tab(pipe_t *new_pipe, token_t **token)
{
    if ((*token)->type != IDENTIFIER) {
        free(new_pipe);
        return NULL;
    }
    // new_pipe->tab_command = realloc_tab_cmd(new_pipe);
    if (!new_pipe->tab_command) {
        free(new_pipe);
        return NULL;
    }
    new_pipe->tab_command[new_pipe->size] = parser_command(token);
    if (!new_pipe->tab_command[new_pipe->size]) {
        free(new_pipe);
        return NULL;
    }
    return new_pipe;
}

static
pipe_t *add_in_tab(pipe_t *new_pipe, token_t **token)
{
    if (!new_pipe || !token)
        return NULL;
    // if (realloc_tab_cmd(new_pipe) == RET_ERROR)
        return NULL;
    if (!new_pipe->tab_command) {
        free(new_pipe);
        return NULL;
    }
    new_pipe->tab_command[new_pipe->size] = parser_command(token);
    if (!new_pipe->tab_command[new_pipe->size]) {
        free(new_pipe);
        return NULL;
    }
    return new_pipe;
}

pipe_t *loop_pipe(pipe_t *new_pipe, token_t **token)
{
    if (!new_pipe || !token)
        return NULL;
    while ((*token) && (*token)->type == PIPE) {
        if ((*token)->next->type != IDENTIFIER) {
            dprintf(2, "Invalid null command.\n");
            free(new_pipe);
            return NULL;
        }
        *token = (*token)->next;
        new_pipe->size += 1;
        new_pipe = add_in_tab(new_pipe, token);
        if (new_pipe == NULL)
            return NULL;
        if (init_fd(new_pipe) == RET_ERROR)
            return NULL;
        if ((*token)->next == NULL) {
            return new_pipe;
        }
    }
    return new_pipe;
}
