/*
** EPITECH PROJECT, 2024
** memory_management_parser
** File description:
** free_parser
*/

#include <stdlib.h>
#include "parser_ast.h"
#include "lexer_ast.h"

static
void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i ++)
        free(tab[i]);
    free(tab);
}

static
void free_command(commands_t *command)
{
    if (command) {
        free(command->exec_name);
        free_tab(command->argv);
        free(command);
    }
}

void free_lexer_list(list_t *list)
{
    for (token_t *tmp = list->head; tmp != NULL; tmp = tmp->next) {
        free(tmp->text);
    }
    free(list->input);
    free(list);
}

void free_parser(root_t *root)
{
    free(root);
}

void free_parser_lexer(root_t *root, __attribute__((unused))list_t *list)
{
    free_parser(root);
}
