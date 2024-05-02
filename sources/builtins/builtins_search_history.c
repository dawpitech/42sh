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
int error_out_of_limit(shell_t *shell)
{
    dprintf(2, "%d: Index out of limit.\n", shell->history_size);
    return RET_ERROR;
}

int execute_search_history(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv)
{
    if (argc >= 2 && strcmp(argv[0], "!") == 0 &&
        argv[1] != NULL && strcmp(argv[1], "--help") == 0)
        return print_help();
    if (atoi(&argv[0][1]) > (int) shell->history_size)
        return error_out_of_limit(shell);
    return RET_VALID;
}
