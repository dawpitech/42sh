/*
** EPITECH PROJECT, 2024
** utils
** File description:
** root_utils
*/

#include "lexer_ast.h"
#include "parser_ast.h"
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int realloc_tab_sc(root_t *root)
{
    if (!root)
        return NULL;
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

root_t *loop_root(root_t *root, token_t **token)
{
    while ((*token) && ((*token)->type == IDENTIFIER ||
        (*token)->type == D_AND)) {
        if (realloc_tab_sc(root) == RET_ERROR) {
            free(root);
            return NULL;
        }
        root->tab_sc[root->size] = parser_semicol(token);
        root->size += 1;
        if (!root || !root->tab_sc[root->size - 1]) {
            free(root);
            return NULL;
        }
        if (!(*token) || (*token)->next == NULL || (*token)->type == END)
            break;
        if ((*token)->type != SEMICOLOMN)
            return NULL;
        if ((*token) != NULL)
            (*token) = (*token)->next;
    }
    return root;
}
