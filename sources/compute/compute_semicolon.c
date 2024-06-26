/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_semicolon header
*/

#include <stdio.h>

#include "minishell.h"

/**
 * This function computes an SEMICOLON node
 * @param semicol a semicolon node
 * @return the return value of the expression
 */
int compute_semicolon(semicol_t *semicol)
{
    int rt_value = RET_ERROR;

    if (semicol == NULL)
        return RET_ERROR;
    for (int i = 0; i < (int) semicol->size; i++)
        rt_value = compute_and(semicol->tab_and[i]);
    return rt_value;
}
