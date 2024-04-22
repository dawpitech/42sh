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
    printf("Usage: history [-chrSLMT] [# number of events].\n");
    return EXIT_SUCCESS_TECH;
}

static
int write_hist(shell_t *shell)
{
    FILE *hist;

    hist = fopen(HISTORY_FILE, "w");
    if (hist == NULL)
        return EXIT_FAILURE_TECH;
    for (int i = 0; i < (int) shell->history_size; i += 1) {
        fprintf(hist, "#+%ld\n", shell->history_entries[i]->timestamp);
        fprintf(hist, "%s\n", shell->history_entries[i]->line);
    }
    fclose(hist);
    return EXIT_SUCCESS_TECH;
}

void load_history(shell_t *shell)
{
    return;
    FILE *hist;
    char *line;
    size_t buffer_value;

    hist = fopen(HISTORY_FILE, "r");
    if (hist == NULL)
        return;
    for (int y = 0; getline(&line, &buffer_value, hist) > 0; y += 1) {

    }
}

int execute_history(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv)
{
    if (argc == 1)
        return print_hist(shell);
    if (argc == 2 && argv[1] != NULL && strcmp(argv[1], "-S") == 0)
        return write_hist(shell);
    if (argc == 2 && argv[1] != NULL && strcmp(argv[1], "--help") == 0)
        return print_help();
    return EXIT_FAILURE_TECH;
}
