/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_pipe header
*/

#include "minishell.h"

/**
 * This function computes a PIPE node
 * @param pipe a PIPE node
 * @return the return value of the expression
 */
int compute_pipe(pipe_t *pipe)
{
    
    return compute_cmd(pipe->tab_command[0]);
}
