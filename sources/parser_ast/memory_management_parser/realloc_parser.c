/*
** EPITECH PROJECT, 2024
** memory_management_parser
** File description:
** realloc_parser
*/

#include "minishell.h"
#include "modifiers.h"
#include "my.h"
#include "parser_ast.h"
#include "lexer_ast.h"
#include <stdlib.h>

static
int my_tablen(char **tab)
{
    int count = 0;

    if (!tab)
        return -1;
    for (; tab[count] != NULL; count ++);
    return count;
}

int realloc_tab_sc(semicol_t *sm)
{
    if (!sm)
        return NULL;
    sm->tab_and = realloc(sm, sm->size + 1);
    sm->tab_and[sm->size] = malloc(sizeof(and_t));
    if (!sm)
        return RET_ERROR;
    sm->tab_and[sm->size + 1] = NULL;
    sm->size += 1;
    free(sm->tab_and);
    return RET_VALID;
}

int realloc_tab_pipe(pipe_t *pipe)
{
    if (!pipe)
        return NULL;
    pipe->tab_command = realloc(pipe, pipe->size + 1);
    pipe->tab_command[pipe->size] = malloc(sizeof(commands_t));
    if (!pipe)
        return RET_ERROR;
    pipe->tab_command[pipe->size + 1] = NULL;
    free(pipe->tab_command);
    return RET_VALID;
}

char **realloc_args(char **old_args, token_t *token)
{
    char **new = NULL;
    int len = 0;
    int i = 0;

    len = my_tablen(old_args);
    if (len == -1)
        new = malloc(sizeof(char *) * 2);
    else
        new = malloc(sizeof(char *) * (len + 2));
    for (i = 0; i < len; i ++) {
        new[i] = old_args[i];
    }
    new[i] = strdup(token->text);
    new[i + 1] = NULL;
    free(old_args);
    return new;
}
