/*
** EPITECH PROJECT, 2024
** utils
** File description:
** semicol_utils
*/

#include "lexer_ast.h"
#include "minishell.h"
#include "parser_ast.h"
#include <stdlib.h>
#include <stdio.h>

int realloc_tab_and(semicol_t *sm)
{
    if (!sm)
        return NULL;
    if (sm->size == 0) {
        sm->tab_and = malloc(sizeof(and_t *) * 2);
    } else {
        printf("%li\n", sm->size);
        sm->tab_and = realloc(sm->tab_and, sizeof(and_t *) * sm->size + 1);
    }
    sm->tab_and[sm->size] = malloc(sizeof(and_t));
    if (!sm)
        return RET_ERROR;
    sm->tab_and[sm->size + 1] = NULL;
    return RET_VALID;
}

semicol_t *loop_semicol(semicol_t *s, token_t **token)
{
    while ((*token)->type == IDENTIFIER && (*token)->type != END) {
        if (realloc_tab_and(s) == RET_ERROR)
            return NULL;
        if (!s->tab_and) {
            free(s);
            return NULL;
        }
        s->tab_and[s->size] = parser_and(token);
        s->size += 1;
        if (!s || !s->tab_and[s->size - 1]) {
            free(s);
            return NULL;
        }
        if (!(*token) || (*token)->type == END || (*token)->type != D_AND)
            return s;
        if (*token != NULL)
            *token = (*token)->next;
    }
    return s;
}
