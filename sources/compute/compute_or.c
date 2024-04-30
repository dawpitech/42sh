/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_or header
*/

#include "minishell.h"

int compute_or(or_t *or)
{
    return compute_pipe(or->tab_pipe[0]);
}
