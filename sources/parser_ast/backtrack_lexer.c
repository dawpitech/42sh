/*
** EPITECH PROJECT, 2024
** parser_ast
** File description:
** backtrack_lexer
*/

#include "lexer_ast.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static
int check_dquote(token_t *tmp, backtrack_t *bt)
{
    token_t *dup = NULL;

    if (tmp->text[0] != '\"')
        return RET_VALID;
    if ((*bt).count_dquote == 1) {
        (*bt).count_dquote = !(*bt).count_dquote;
        return RET_VALID;
    }
    (*bt).is_dquote = !(*bt).is_dquote;
    (*bt).count_dquote = !(*bt).count_dquote;
    dup = tmp->next;
    for (; dup != NULL; dup = dup->next)
        if (dup->text[0] == '\"') {
            (*bt).is_dquote = !(*bt).is_dquote;
            break;
        }
    if ((*bt).is_dquote != 0)
        return dprintf(2, "Unmatched '\"'.\n");
    return RET_VALID;
}

static
int check_squote(token_t *tmp, backtrack_t *bt)
{
    token_t *dup = NULL;

    if (tmp->text[0] != '\'')
        return RET_VALID;
    if ((*bt).count_squote == 1) {
        (*bt).count_squote = !(*bt).count_squote;
        return RET_VALID;
    }
    (*bt).is_squote = !(*bt).is_squote;
    (*bt).count_squote = !(*bt).count_squote;
    dup = tmp->next;
    for (; dup != NULL; dup = dup->next)
        if (dup->text[0] == '\'') {
            (*bt).is_squote = !(*bt).is_squote;
            break;
        }
    if ((*bt).is_squote != 0)
        return dprintf(2, "Unmatched '\''.\n");
    return RET_VALID;
}

static
int check_matching_parenthese(token_t *origin, backtrack_t *bt)
{
    int matching = 0;
    token_t *ptr = origin;

    while (ptr != NULL) {
        if (ptr->type == L_PAREN)
            matching += 1;
        if (ptr->type == R_PAREN) {
            matching += 1;
            break;
        }
        if (check_dquote(ptr, bt) != RET_VALID ||
            check_squote(ptr, bt) != RET_VALID)
            return RET_ERROR;
        ptr = ptr->next;
    }
    if (matching == 2)
        return RET_VALID;
    return 84;
}

static
int check_loops(backtrack_t *bt)
{
    if ((*bt).loop_count == 4 && (*bt).count_paren == 3)
        return dprintf(2, "Too many )'s.\n");
    if ((*bt).loop_count >= 2 && (*bt).count_paren == 1)
        return dprintf(2, "Badly placed ().\n");
    return RET_VALID;
}

static
int check_parenthese(token_t *token, backtrack_t *bt)
{
    if (token->type != L_PAREN && token->type != R_PAREN)
        return RET_VALID;
    if ((*bt).count_paren == 1) {
        token = token->next;
        (*bt).count_paren += 1;
        return RET_VALID;
    }
    if (token->type == R_PAREN)
        return dprintf(2, "Too many )'s.\n");
    if (token->next && token->type == L_PAREN && token->next->type == R_PAREN)
        return dprintf(2, "Invalid null command.\n");
    if (check_matching_parenthese(token, bt) == 1)
        return RET_ERROR;
    else if (check_matching_parenthese(token, bt) == 84)
        return dprintf(2, "Too many ('s.\n");
    (*bt).count_paren += 1;
    if (check_loops(bt) != 0)
        return RET_ERROR;
    return RET_VALID;
}

int backtrack_lexer(token_t *token)
{
    backtrack_t bt = {0};

    if (!token)
        return RET_ERROR;
    for (token_t *tmp = token; tmp != NULL; tmp = tmp->next) {
        bt.loop_count += 1;
        if (check_parenthese(tmp, &bt) != 0)
            return RET_ERROR;
        if (check_dquote(tmp, &bt) != 0)
            return RET_ERROR;
        if (check_squote(tmp, &bt) != 0)
            return RET_ERROR;
        if (tmp->type == SEMICOLOMN)
            bt.loop_count = 0;
    }
    return RET_VALID;
}
