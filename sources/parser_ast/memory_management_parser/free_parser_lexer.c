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

static
void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i ++)
        free(tab[i]);
    free(tab);
}

void free_lexer_list(list_t *list)
{
    for (token_t *tmp = list->head; tmp != NULL; tmp = tmp->next) {
        free(tmp->text);
    }
    free(list->input);
    free(list);
}

static
void free_command(pipe_t *pipe)
{
    for (size_t i = 0; pipe->size > i; i ++) {
        if (pipe->tab_command[i]->sub_shell != NULL)
            free_parser(pipe->tab_command[i]->sub_shell);
        if (!pipe->tab_command[i]->sub_shell) {
            free_tab(pipe->tab_command[i]->argv);
            free(pipe->tab_command[i]->exec_name);
        }
    }
}

static
void free_pipe(or_t *or_obj)
{
    for (size_t i = 0; or_obj->size > i; i ++) {
        free_command(or_obj->tab_pipe[i]);
        free(or_obj->tab_pipe[i]);
    }
}

static
void free_or(and_t *and_obj)
{
    for (size_t i = 0; and_obj->size > i; i ++) {
        free_pipe(and_obj->tab_or[i]);
        free(and_obj->tab_or[i]);
    }
}

static
void free_and(semicol_t *sm)
{
    for (size_t i = 0; sm->size > i; i ++) {
        free_or(sm->tab_and[i]);
        free(sm->tab_and[i]);
    }
}

static
void free_semicol(root_t *root)
{
    for (size_t i = 0; root->size > i; i ++) {
        free_and(root->tab_sc[i]);
        free(root->tab_sc[i]);
    }
}

void free_parser(root_t *root)
{
    free_semicol(root);
}
