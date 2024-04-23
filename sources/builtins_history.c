/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** builtins_history header
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "minishell.h"
#include "builtins_cmd.h"

static
int print_hist(shell_t *shell)
{
    history_entry_t *entry;

    for (int i = 0; i < (int) shell->history_size; i += 1) {
        entry = history_get(shell, i);
        printf("     %d  %02d:%02d   %s\n", i + 1,
            localtime(&entry->timestamp)->tm_hour,
            localtime(&entry->timestamp)->tm_min,
            entry->line);
    }
    return EXIT_SUCCESS_TECH;
}

static
int print_help(void)
{
    printf("Usage: history [-SL].\n");
    return EXIT_SUCCESS_TECH;
}

int execute_history(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv)
{
    if (argc == 1)
        return print_hist(shell);
    if (argc == 2 && argv[1] != NULL && strcmp(argv[1], "-L") == 0)
        return load_history(shell);
    if (argc == 2 && argv[1] != NULL && strcmp(argv[1], "-S") == 0)
        return write_hist(shell);
    if (argc == 2 && argv[1] != NULL && strcmp(argv[1], "--help") == 0)
        return print_help();
    return EXIT_FAILURE_TECH;
}
