/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_and header
*/

#include "minishell.h"

int compute_and(and_t *and)
{
    return compute_or(and->tab_or[0]);
}
