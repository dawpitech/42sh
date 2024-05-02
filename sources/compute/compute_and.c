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
 * @param and an and node
 * @return the return value of the expression
 */
int compute_and(and_t *and)
{
    int rt_value = RET_ERROR;
    bool last_was_successful = true;

    if (and == NULL || and->size == 0)
        return RET_ERROR;
    if (and->size == 1)
        return compute_or(and->tab_or[0]);
    for (int i = 0; (i < (int) and->size) && last_was_successful; i++) {
        rt_value = compute_or(and->tab_or[i]);
        last_was_successful = (rt_value == RET_VALID) ? true : false;
    }
    return rt_value;
}
