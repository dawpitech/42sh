/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_or header
*/

#include <stdio.h>

#include "minishell.h"

/**
 * This function computes an OR node
 * @param or an or node
 * @return the return value of the expression
 */
int compute_or(or_t *or)
{
    int rt_value = RET_ERROR;
    bool last_was_unsuccessful = true;

    if (or == NULL || or->size == 0)
        return RET_ERROR;
    if (or->size == 1)
        return compute_pipe(or->tab_pipe[0]);
    for (int i = 0; (i < (int) or->size) && last_was_unsuccessful; i++) {
        rt_value = compute_pipe(or->tab_pipe[i]);
        last_was_unsuccessful = (rt_value != RET_VALID) ? true : false;
    }
    return rt_value;
}
