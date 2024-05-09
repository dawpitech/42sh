/*
** EPITECH PROJECT, 2024
** utils
** File description:
** pipe_utils
*/

#include "minishell.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "lexer_ast.h"

int init_fd(pipe_t *s_pipe)
{
    int fd[2] = {0};

    if (pipe(fd) == -1) {
        return RET_ERROR;
    }
    s_pipe->tab_command[s_pipe->size - 1]->fd_in = fd[0];
    s_pipe->tab_command[s_pipe->size - 2]->fd_out = fd[1];
    return RET_VALID;
}

int realloc_tab_cmd(pipe_t *p)
{
    if (!p)
        return RET_ERROR;
    if (p->size == 0)
        p->tab_command = malloc(sizeof(commands_t *) * 2);
    else
        p->tab_command = realloc(p->tab_command,
            sizeof(commands_t) * (p->size + 2));
    p->tab_command[p->size] = malloc(sizeof(commands_t));
    if (!p->tab_command || !p->tab_command[p->size])
        return RET_ERROR;
    p->tab_command[p->size + 1] = NULL;
    return RET_VALID;
}

void fill_arguments(token_t **token, commands_t *c)
{
    while ((*token) && ((*token)->type == IDENTIFIER ||
        (*token)->type == OPERATOR)) {
        c->argv = realloc(c->argv, sizeof(char *) * (c->argc + 2));
        c->argv[c->argc] = handle_operator(token);
        c->argc += 1;
        c->argv[c->argc] = NULL;
        (*token) = (*token)->next;
    }
}

static
int add_command(pipe_t *new_pipe, token_t **token, int idx, shell_t *shell)
{
    commands_t *c = malloc(sizeof(commands_t));

    c->exec_name = handle_operator(token);
    c->argv = malloc(sizeof(char *) * 2);
    c->argv[0] = strdup(c->exec_name);
    compare_alias(shell->aliases, c);
    c->argv[1] = NULL;
    c->argc = 1;
    c->fd_in = STDIN_FILENO;
    c->fd_out = STDOUT_FILENO;
    c->shell = shell;
    c->sub_shell = NULL;
    c->job_control = false;
    (*token) = (*token)->next;
    fill_arguments(token, c);
    new_pipe->tab_command[idx] = c;
    new_pipe->size += 1;
    return RET_VALID;
}

static
int handle_pipe(pipe_t *new_pipe, token_t **token, int idx, shell_t *shell)
{
    if (!(*token) || (*token)->type != PIPE)
        return RET_VALID;
    if ((*token)->next->type != IDENTIFIER
        && (*token)->next->type != OPERATOR) {
        dprintf(2, "Invalid null command.\n");
        free(new_pipe);
        return RET_ERROR;
    }
    (*token) = (*token)->next;
    if (realloc_tab_cmd(new_pipe) == RET_ERROR)
        return RET_ERROR;
    if (add_command(new_pipe, token, idx, shell) == RET_ERROR)
        return RET_ERROR;
    if (init_fd(new_pipe) == RET_ERROR)
        return RET_ERROR;
    return RET_VALID;
}

static
int handle_redirection(pipe_t *new_pipe, token_t **token, shell_t *shell)
{
    while (*token && ((*token)->type == PIPE || (*token)->type == IN ||
        (*token)->type == D_IN || (*token)->type == OUT ||
        (*token)->type == D_OUT)) {
        if (handle_pipe(new_pipe, token, new_pipe->size, shell) == RET_ERROR)
            return RET_ERROR;
        if (loop_redirect(new_pipe, token) == NULL) {
            return RET_ERROR;
        }
    }
    return RET_VALID;
}

static
int handle_job_control(token_t *t, pipe_t *p, int idx)
{
    if (!t || t->type != AND)
        return RET_ERROR;
    p->tab_command[idx - 1]->job_control = true;
    t = t->next;
    return RET_VALID;
}

pipe_t *loop_pipe(pipe_t *new_pipe, token_t **t, shell_t *shell)
{
    if (!new_pipe || !t)
        return NULL;
    while ((*t) && ((*t)->type == IDENTIFIER ||
        (*t)->type == OPERATOR || (*t)->type == L_PAREN ||
        (*t)->type == R_PAREN || (*t)->type == AND)) {
        if (realloc_tab_cmd(new_pipe) == RET_ERROR)
            return NULL;
        if ((*t)->type == L_PAREN &&
            handle_parenthese(new_pipe, t, shell) == 0)
            return new_pipe;
        if (add_command(new_pipe, t, new_pipe->size, shell) == RET_ERROR)
            return NULL;
        if (handle_job_control((*t), new_pipe, new_pipe->size) == RET_VALID)
            return new_pipe;
        if (handle_redirection(new_pipe, t, shell) == RET_ERROR)
            return NULL;
        if (!(*t) || (*t)->type == END || (*t)->type != PIPE)
            break;
    }
    return new_pipe;
}
