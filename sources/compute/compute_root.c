/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_root header
*/

#include "minishell.h"

/**
 * This function computes the return value an AST
 * @param root the root of an ast
 * @return the return value of the whole ast
 */
int compute_root(root_t *root)
{
    int rt_value = RET_ERROR;

    if (root == NULL)
        return RET_ERROR;
    for (int i = 0; i < (int) root->size; i++)
        rt_value = compute_semicolon(root->tab_sc[i]);
    return rt_value;
}
