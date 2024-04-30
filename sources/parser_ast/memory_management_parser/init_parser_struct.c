/*
** EPITECH PROJECT, 2024
** initialization
** File description:
** init_parser_struct
*/

#include "minishell.h"
#include <stdlib.h>

pipe_t *init_pipe(void)
{
    pipe_t *new_pipe = malloc(sizeof(pipe_t));

    if (!new_pipe)
        return NULL;
    new_pipe->size = 0;
    new_pipe->tab_command = NULL;
    return new_pipe;
}

semicol_t *init_semicol(void)
{
    semicol_t *new = malloc(sizeof(semicol_t));

    if (!new)
        return NULL;
    new->size = 0;
    new->tab_and = NULL;
    return new;
}

root_t *init_root(void)
{
    root_t *root = malloc(sizeof(root_t));

    if (!root)
        return NULL;
    root->size = 0;
    root->tab_sc = NULL;
    return root;
}

or_t *init_or(void)
{
    or_t *new = malloc(sizeof(or_t));

    if (!new)
        return NULL;
    new->size = 0;
    new->tab_pipe = NULL;
    return new;
}

and_t *init_and(void)
{
    and_t *new = malloc(sizeof(and_t));

    if (!new)
        return NULL;
    new->size = 0;
    new->tab_or = NULL;
    return new;
}
