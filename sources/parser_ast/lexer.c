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
#include "minishell.h"
static
token_t *init_node(token_t *new)
{
    new = malloc(sizeof(token_t));
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
    if (!list)
        return;
    while (isspace(list->input[list->cursor])) {
        list->cursor += 1;
    }
}

static
token_t *next_token(list_t *list, token_t *node)
{
    node = init_node(node);
    remove_space(list);
    if (list->cursor >= list->input_len) {
        return node;
    }
    if (is_operator(list, node) == 1)
        return node;
    if (my_ispipe(list, node) == 1)
        return node;
    if (my_isand(list, node) == 1)
        return node;
    if (my_issemicol(list, node) == 1)
        return node;
    if (my_isredirect_command_to_file(list, node) == 1)
        return node;
    if (my_isredirect_file_to_command(list, node) == 1)
        return node;
    if (my_isalphanum(list, node) == 0)
        return node;
    return node;
}

list_t *lexer(shell_t *mysh, list_t *list)
{
    token_t *tmp = NULL;
    token_t *prev = NULL;
    int i = 0;

    if (!mysh || strlen(mysh->prompt->raw_input) <= 0)
        return NULL;
    list = init_list(list, mysh->prompt->raw_input);
    list->head = init_node(list->head);
    while (list->cursor < list->input_len && i < 15) {
        tmp = next_token(list, init_node(NULL));
        if (tmp->type == INVALID)
            return NULL;
        if (prev == NULL)
            list->head = tmp;
        else
            prev->next = tmp;
        prev = tmp;
        i += 1;
        printf("%s %d\n", prev->text, prev->type);
    }
    return list;
}
