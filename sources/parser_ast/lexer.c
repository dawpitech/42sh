/*
** EPITECH PROJECT, 2024
** test_lexer
** File description:
** lexer
*/

#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer_ast.h"

static
token_t *init_node(void)
{
    token_t *new = malloc(sizeof(token_t));

    if (!new)
        return NULL;
    new->next = NULL;
    new->text = NULL;
    new->type = END;
    return new;
}

list_t *init_list(list_t *new, char *input)
{
    if (new != NULL)
        free_lexer_list(new);
    new = malloc(sizeof(list_t));
    if (!new)
        return NULL;
    new->head = NULL;
    new->cursor = 0;
    new->input = strdup(input);
    new->input_len = strlen(input);
    return new;
}

static
void remove_space(list_t *list)
{
    if (!list || list->cursor >= list->input_len)
        return;
    while (isspace(list->input[list->cursor])) {
        list->cursor += 1;
    }
}

static
token_t *next_token(list_t *list, token_t *node)
{
    remove_space(list);
    if (list->cursor >= list->input_len)
        return node;
    if (is_operator(list, node) == 1 || is_operator(list, node) == 84)
        return node;
    if (my_isparenthese(list, node) == 1)
        return node;
    if (my_ispipe(list, node) == 1)
        return node;
    if (my_isand(list, node) == 1)
        return node;
    if (my_issemicol(list, node) == 1)
        return node;
    if (is_redirection(list, node) == 1)
        return node;
    if (my_isalphanum(list, node) == 0)
        return node;
    return node;
}

list_t *lexer(char *raw_input, list_t *list)
{
    token_t *tmp = NULL;
    token_t *prev = NULL;

    if (!raw_input || strlen(raw_input) <= 0)
        return NULL;
    list = init_list(list, raw_input);
    while (1) {
        tmp = next_token(list, init_node());
        if (tmp->type == END) {
            free(tmp);
            break;
        }
        if (prev == NULL)
            list->head = tmp;
        else
            prev->next = tmp;
        prev = tmp;
    }
    return list;
}
