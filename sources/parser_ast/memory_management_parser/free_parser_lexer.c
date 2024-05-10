/*
** EPITECH PROJECT, 2024
** memory_management_parser
** File description:
** free_parser
*/

#include <iso646.h>
#include <stdlib.h>
#include "minishell.h"
#include "lexer_ast.h"

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i ++)
        free(tab[i]);
    free(tab);
}

void free_lexer_list(list_t *list)
{
    token_t *prev = NULL;
    token_t *tmp = list->head;

    while (tmp != NULL) {
        free(tmp->text);
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
    free(list->input);
    free(list);
}

static
void free_command(pipe_t *pipe)
{
    if (!pipe)
        return;
    for (size_t i = 0; pipe->size > i; i ++) {
        if (pipe->tab_command[i]->sub_shell != NULL)
            free_parser(pipe->tab_command[i]->sub_shell);
        if (!pipe->tab_command[i]->sub_shell) {
            free_tab(pipe->tab_command[i]->argv);
            free(pipe->tab_command[i]->exec_name);
        }
        free(pipe->tab_command[i]);
    }
    free(pipe->tab_command[pipe->size]);
    free(pipe->tab_command);
    pipe->tab_command = NULL;
}

static
void free_pipe(or_t *or_obj)
{
    if (!or_obj)
        return;
    for (size_t i = 0; or_obj->size >= i; i ++) {
        free_command(or_obj->tab_pipe[i]);
        free(or_obj->tab_pipe[i]);
    }
    free(or_obj->tab_pipe[or_obj->size]);
    free(or_obj->tab_pipe);
    or_obj->tab_pipe = NULL;
}

static
void free_or(and_t *and_obj)
{
    if (!and_obj)
        return;
    for (size_t i = 0; and_obj->size >= i; i ++) {
        free_pipe(and_obj->tab_or[i]);
        free(and_obj->tab_or[i]);
    }
    free(and_obj->tab_or[and_obj->size]);
    free(and_obj->tab_or);
    and_obj->tab_or = NULL;
}

static
void free_and(semicol_t *sm)
{
    if (!sm)
        return;
    for (size_t i = 0; sm->size >= i; i ++) {
        free_or(sm->tab_and[i]);
        free(sm->tab_and[i]);
    }
    free(sm->tab_and[sm->size]);
    free(sm->tab_and);
    sm->tab_and = NULL;
}

static
void free_semicol(root_t *root)
{
    if (!root)
        return;
    for (size_t i = 0; root->size >= i; i ++) {
        free_and(root->tab_sc[i]);
        free(root->tab_sc[i]);
    }
    free(root->tab_sc[root->size]);
    free(root->tab_sc);
    root->tab_sc = NULL;
}

void free_parser(root_t *root)
{
    if (root == NULL)
        return;
    free_semicol(root);
    free(root);
}
