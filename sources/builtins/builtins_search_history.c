/*
** EPITECH PROJECT, 2024
** builtins
** File description:
** builtins_search_history
*/

#include "minishell.h"
#include "builtins_cmd.h"
#include <stdio.h>
#include <stdlib.h>

static
int print_help(void)
{
    printf("Usage: !(number).\n");
    return RET_VALID;
}

static
int error_out_of_limit(char *nbr)
{
    dprintf(2, "%s: Index out of limit.\n", nbr);
    return EXIT_FAILURE;
}

static
int exec_history_command(shell_t *shell, int index)
{
    root_t *root = NULL;

    root = parse_input(shell->history_entries[index]->line, shell);
    if (root == NULL)
        return RET_ERROR;
    return compute_root(root);
}

int execute_search_history(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv)
{
    if (argc >= 2 && strcmp(argv[0], "!") == 0 &&
        argv[1] != NULL && strcmp(argv[1], "--help") == 0)
        return print_help();
    if (atoi(argv[1]) > (int) shell->history_size - 2) {
        return error_out_of_limit(argv[1]);
    }
    return exec_history_command(shell, atoi(argv[1]));
}
