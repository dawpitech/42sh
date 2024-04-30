/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_pipe header
*/

#include "minishell.h"

/**
 * This function computes the return value of a cmd_t
 * @param pipe
 * @return
 */
int compute_pipe(pipe_t *pipe)
{
    return compute_cmd(pipe->tab_command[0]);
}
