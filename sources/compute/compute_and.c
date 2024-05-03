/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_and header
*/

#include <stdio.h>

#include "minishell.h"

/**
 * This function computes an AND node
 * @param and_obj an and node
 * @return the return value of the expression
 */
int compute_and(and_t *and_obj)
{
    int rt_value = RET_ERROR;
    bool last_was_successful = true;

    if (and_obj == NULL || and_obj->size == 0)
        return RET_ERROR;
    if (and_obj->size == 1)
        return compute_or(and_obj->tab_or[0]);
    for (int i = 0; (i < (int) and_obj->size) && last_was_successful; i++) {
        rt_value = compute_or(and_obj->tab_or[i]);
        last_was_successful = (rt_value == RET_VALID) ? true : false;
    }
    return rt_value;
}
