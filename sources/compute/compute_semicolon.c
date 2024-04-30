#include <stdio.h>
#include "minishell.h"

/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_semicolon header
*/

/**
 * This function computes the return value of a and_t\n
 * Contrary to it's name it computes the AND operator
 * @param semicol a semicolon node
 * @return the return value of the expression
 */
int compute_semicolon(semicol_t *semicol)
{
    int rt_value = RET_ERROR;
    bool last_was_successful = true;

    if (semicol == NULL || semicol->size == 0)
        return RET_ERROR;
    if (semicol->size == 1)
        return compute_and(semicol->tab_and[0]);
    for (int i = 0; (i < (int) semicol->size) && last_was_successful; i++) {
        rt_value = compute_and(semicol->tab_and[i]);
        last_was_successful = (rt_value == RET_VALID) ? true : false;
    }
    return rt_value;
}
