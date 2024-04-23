/*
** EPITECH PROJECT, 2024
** utils
** File description:
** semicol_utils
*/

#include "lexer_ast.h"
#include "parser_ast.h"
#include <stdlib.h>

semicol_t *loop_semicol(semicol_t *new, token_t **token)
{
    // while ((*token)->type == IDENTIFIER && (*token)->type != END) {
    //     // new->tab_and = realloc_tab_and(new);
    //     if (!new->tab_and) {
    //         free(new);
    //         return NULL;
    //     }
    //     new->tab_and[new->size] = parser_and(token);
    //     if (!new || !new->tab_and[new->size]) {
    //         free(new);
    //         return NULL;
    //     }
    //     if (!(*token) || (*token)->type == END)
    //         return new;
    //     new->size += 1;
    //     if ((*token)->type != PIPE)
    //         return new;
    //     if (*token != NULL)
    //         *token = (*token)->next;
    // }
    return new;
}
