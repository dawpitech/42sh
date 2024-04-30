/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_pipe header
*/

#include "minishell.h"

int compute_pipe(pipe_t *pipe)
{
    return compute_cmd(pipe->tab_command[0]);
}
