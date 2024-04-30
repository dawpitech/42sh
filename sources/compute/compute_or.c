/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_or header
*/

#include <stdio.h>

#include "minishell.h"

/**
 * This function computes the return value of a pipe_t\n
 * Contrary to it's name it computes the PIPE operator
 * @param or an or node
 * @return the return value of the expression
 */
int compute_or(or_t *or)
{
    return compute_pipe(or->tab_pipe[0]);
}
