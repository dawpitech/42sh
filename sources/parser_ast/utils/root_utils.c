/*
** EPITECH PROJECT, 2024
** utils
** File description:
** root_utils
*/

#include "lexer_ast.h"
#include "parser_ast.h"
#include <stdlib.h>

root_t *loop_root(root_t *root, token_t **token)
{
    while ((*token) && (*token)->type == IDENTIFIER) {
        root->tab_sc = realloc_tab_sc(root);
        if (!root->tab_sc) {
            free(root);
            return NULL;
        }
        root->tab_sc[root->size] = parser_semicol(token);
        if (!root || !root->tab_sc[root->size]) {
            free(root);
            return NULL;
        }
        if ((*token) == NULL || (*token)->type == END)
            break;
        if ((*token)->type != SEMICOLOMN)
            return NULL;
        if ((*token) != NULL)
            (*token) = (*token)->next;
        root->size += 1;
    }
    return root;
}
