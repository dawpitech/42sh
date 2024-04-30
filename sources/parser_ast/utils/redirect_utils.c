/*
** EPITECH PROJECT, 2024
** utils
** File description:
** redirect_utils
*/

#include "minishell.h"
#include "lexer_ast.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
**
** This function mangage the redirect out ('>') to the file linked
**
*/
static
pipe_t *redirect_out(pipe_t *new_pipe, token_t **token)
{
    int filefd = 0;

    if ((*token)->next->type == IDENTIFIER)
        (*token) = (*token)->next;
    else
        return NULL;
    filefd = open((*token)->text, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    new_pipe->tab_command[new_pipe->size - 1]->fd_out = filefd;
    (*token) = (*token)->next;
    return new_pipe;
}

/*
**
** This function mangage the redirect out ('>>') to the file linked
**
*/
static
pipe_t *redirect_d_out(pipe_t *new_pipe, token_t **token)
{
    int filefd = 0;

    if ((*token)->next->type == IDENTIFIER)
        (*token) = (*token)->next;
    else
        return NULL;
    filefd = open((*token)->text, O_CREAT | O_APPEND | O_WRONLY, 0666);
    new_pipe->tab_command[new_pipe->size]->fd_out = filefd;
    (*token) = (*token)->next;
    return new_pipe;
}

/*
**
** This function mangage the redirect in ('<') to the file linked
**
*/
static
pipe_t *redirect_in(pipe_t *new_pipe, token_t **token)
{
    int filefd = 0;

    if ((*token)->next->type == IDENTIFIER)
        (*token) = (*token)->next;
    else
        return NULL;
    filefd = open((*token)->text, O_RDONLY);
    if (filefd < 0) {
        dprintf(1, "%s: No such file or directory\n", (*token)->text);
        return NULL;
    }
    new_pipe->tab_command[new_pipe->size]->fd_in = filefd;
    (*token) = (*token)->next;
    return new_pipe;
}

static
char *get_redirect_d_in_buffer(char *patern)
{
    char *input = 0;
    size_t len = 0;
    char *str = 0;

    while (getline(&input, &len, stdin) != -1) {
        input = strndup(input, strlen(input) - 1);
        if (!str) {
            str = strdup(input);
            str = strcat(str, "\n");
        } else {
            str = strcat(str, input);
            str = strcat(str, "\n");
        }
        if (strcmp(input, patern) == 0) {
            free(input);
            return str;
        }
        dprintf(1, "? ");
    }
    return str;
}

/*
**
** This function mangage the redirect in ('<<') to the file linked
**
*/
static
pipe_t *redirect_d_in(pipe_t *new_pipe, token_t **token)
{
    char *str = 0;
    int filefd = 0;

    if ((*token)->next->type == IDENTIFIER)
        (*token) = (*token)->next;
    else
        return NULL;
    dprintf(1, "? ");
    str = get_redirect_d_in_buffer((*token)->text);
    if (!str)
        return NULL;
    filefd = open("./tmp/d_inner", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (write(filefd, str, strlen(str)) == -1)
        return NULL;
    close(filefd);
    filefd = open("./tmp/d_inner", O_RDONLY);
    new_pipe->tab_command[new_pipe->size]->fd_in = filefd;
    (*token) = (*token)->next;
    return new_pipe;
}

pipe_t *check_redirect_symbol(pipe_t *new_pipe, token_t **token)
{
    if (!new_pipe || !token)
        return NULL;
    if ((*token)->type == OUT)
        new_pipe = redirect_out(new_pipe, token);
    if ((*token)->type == D_OUT)
        new_pipe = redirect_d_out(new_pipe, token);
    if ((*token)->type == IN)
        new_pipe = redirect_in(new_pipe, token);
    if ((*token)->type == D_IN)
        new_pipe = redirect_d_in(new_pipe, token);
    return new_pipe;
}

pipe_t *loop_redirect(pipe_t *new_pipe, token_t **token)
{
    while ((*token) && ((*token)->type == IN || (*token)->type == D_IN ||
        (*token)->type == OUT || (*token)->type == D_OUT)) {
        if ((*token)->next->type != IDENTIFIER) {
            dprintf(2, "Missing name for redirect.\n");
            return NULL;
        }
        new_pipe = check_redirect_symbol(new_pipe, token);
    }
    return new_pipe;
}
