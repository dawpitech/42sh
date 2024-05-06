/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_root header
*/

#include "minishell.h"

int compute_root(root_t *root)
{
    int rt_value = RET_ERROR;

    if (root == NULL)
        return RET_ERROR;
    for (int i = 0; i < (int) root->size; i++)
        rt_value = compute_semicolon(root->tab_sc[i]);
    return rt_value;
}
