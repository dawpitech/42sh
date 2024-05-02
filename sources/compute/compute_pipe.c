/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_pipe header
*/

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

/**
 * This function computes a PIPE node
 * @param pipe_obj a PIPE node
 * @return the return value of the expression
 */
int compute_pipe(pipe_t *pipe_obj)
{
    int fd[2] = {0};
    int rt_value = RET_ERROR;

    if (pipe_obj == NULL || pipe_obj->size == 0)
        return RET_ERROR;
    if (pipe_obj->size == 1)
        return compute_cmd(pipe_obj->tab_command[0]);
    for (int i = 1; i < (int) pipe_obj->size; i++) {
        printf("Looping for pipe\n");
        if (pipe(fd) == -1)
            return RET_ERROR;
        pipe_obj->tab_command[i]->fd_in = fd[0];
        pipe_obj->tab_command[i - 1]->fd_out = fd[1];
    }
    for (int i = 0; i < (int) pipe_obj->size; i++)
        rt_value = compute_cmd(pipe_obj->tab_command[i]);
    return rt_value;
}
