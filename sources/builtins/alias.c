/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** exit_cmd header
*/

#include "alias.h"
#include "minishell.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int count_aliases(alias_t **aliases)
{
    int count = 0;

    for (int i = 0; aliases[i] != NULL; i ++){
        count ++;
    }
    return count;
}

int print_alias(alias_t **aliases)
{
    int i = 0;

    if (aliases == NULL){
        return -1;
    } else {
        while (aliases[i] != NULL) {
            printf("%s", aliases[i]->alias);
            printf("\t%s\n", aliases[i]->cmd);
            i++;
        }
    }
    return EXIT_SUCCESS_TECH;
}

int handle_null(shell_t *shell, char **argv)
{
    shell->aliases = malloc(sizeof(alias_t *) * sizeof(alias_t *));
    shell->aliases[0] = malloc(sizeof(alias_t));
    shell->aliases[0]->alias = strdup(argv[1]);
    shell->aliases[0]->cmd = strdup(argv[2]);
    shell->aliases[1] = NULL;
    return EXIT_FAILURE_TECH;
}

int handle_realoc(shell_t *shell, char **argv)
{
    int i = 0;

    shell->aliases = realloc(shell->aliases,
    sizeof(alias_t *) + count_aliases(shell->aliases));
    for (i = 0; shell->aliases[i] != NULL; i ++);
    shell->aliases[i] = malloc(sizeof(alias_t));
    shell->aliases[i]->alias = strdup(argv[1]);
    shell->aliases[i]->cmd = strdup(argv[2]);
    shell->aliases[i + 1] = NULL;
    return EXIT_SUCCESS_TECH;
}

int alias_handler(shell_t *shell, int argc, char **argv)
{
    if (argc > 3) {
        my_put_stderr("alias: Too many arguments.\n");
        return EXIT_FAILURE_TECH;
    }
    if (argc == 1){
        print_alias(shell->aliases);
        return EXIT_FAILURE_TECH;
    }
    if (argc < 2) {
        my_put_stderr("alias: Too few arguments.\n");
        return EXIT_FAILURE_TECH;
    }
    if (shell->aliases == NULL){
        handle_null(shell, argv);
    } else {
        handle_realoc(shell, argv);
        return EXIT_SUCCESS_TECH;
    }
    return EXIT_FAILURE_TECH;
}
