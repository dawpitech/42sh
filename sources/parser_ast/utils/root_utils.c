/*
** EPITECH PROJECT, 2024
** utils
** File description:
** root_utils
*/

#include "lexer_ast.h"
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int realloc_tab_sc(root_t *root)
{
    if (!root)
        return RET_ERROR;
    if (root->size == 0)
        root->tab_sc = malloc(sizeof(semicol_t *) * 2);
    else
        root->tab_sc = realloc(root->tab_sc,
            sizeof(semicol_t *) * (root->size + 2));
    root->tab_sc[root->size] = malloc(sizeof(semicol_t));
    if (!root->tab_sc)
        return RET_ERROR;
    root->tab_sc[root->size + 1] = NULL;
    return RET_VALID;
}

root_t *loop_root(root_t *root, token_t **t, shell_t *shell)
{
    while ((*t) && ((*t)->type == IDENTIFIER || (*t)->type == D_AND ||
        (*t)->type == OPERATOR || (*t)->type == L_PAREN ||
        (*t)->type == AND)) {
        if (realloc_tab_sc(root) == RET_ERROR)
            return NULL;
        root->tab_sc[root->size] = parser_semicol(t, shell);
        root->size += 1;
        if (!root || !root->tab_sc[root->size - 1]) {
            free(root);
            return NULL;
        }
        if (!(*t) || (*t)->next == NULL || (*t)->type == END)
            break;
        if ((*t)->type != SEMICOLOMN)
            return NULL;
        if ((*t) != NULL)
            (*t) = (*t)->next;
    }
    return root;
}
