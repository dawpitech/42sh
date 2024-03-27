/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** pipe_handler header
*/

#include <unistd.h>

#include "minishell.h"
#include "pipe_handler.h"

int handle_pipe(prompt_t *p)
{
    int fd[2];

    if (p->nb_commands < 2)
        return RET_ERROR;
    if (p->commands[p->nb_commands - 2].type != PIPE)
        return RET_VALID;
    if (pipe(fd) == -1)
        return RET_ERROR;
    p->commands[p->nb_commands - 2].fd_stdout = fd[1];
    p->commands[p->nb_commands - 1].fd_stdin = fd[0];
    return RET_VALID;
}
