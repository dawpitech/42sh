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
 * @param or_obj an or node
 * @return the return value of the expression
 */
int compute_or(or_t *or_obj)
{
    int rt_value = RET_ERROR;
    bool last_was_unsuccessful = true;

    if (or_obj == NULL || or_obj->size == 0)
        return RET_ERROR;
    if (or_obj->size == 1)
        return compute_pipe(or_obj->tab_pipe[0]);
    for (int i = 0; (i < (int) or_obj->size) && last_was_unsuccessful; i++) {
        rt_value = compute_pipe(or_obj->tab_pipe[i]);
        last_was_unsuccessful = (rt_value != RET_VALID) ? true : false;
    }
    return rt_value;
}
