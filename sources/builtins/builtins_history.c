/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** builtins_history header
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#include "minishell.h"
#include "builtins_cmd.h"
#include "history.h"

static
int count_digits(unsigned int n)
{
    if (n / 10 == 0)
        return 1;
    return 1 + count_digits(n / 10);
}

static
void print_hist_line(history_entry_t *entry, history_params_t *params, int i)
{
    if (params->hiding_ln) {
        if (params->timestamp_as_comment)
            printf("#+%ld\n", entry->timestamp);
        printf("%s\n", entry->line);
    } else {
        for (int k = 0; k < 6 - count_digits(i + 1); k += 1)
            printf(" ");
        printf("%d  %02d:%02d   %s\n", i + 1,
            localtime(&entry->timestamp)->tm_hour,
            localtime(&entry->timestamp)->tm_min,
            entry->line);
    }
}

static
int print_hist(shell_t *shell, history_params_t *params)
{
    int lines_nb = (params->nb_lignes_to_print == 0) ?
        (int) shell->history_size :
        (int) params->nb_lignes_to_print;

    if (params->reverse_order) {
        for (int i = (int) shell->history_size - 1;
            i >= (int) shell->history_size; i -= 1)
            print_hist_line(history_get(shell, i), params, i);
    } else {
        for (int i = (int) shell->history_size - lines_nb;
            i < (int)shell->history_size; i += 1)
            print_hist_line(history_get(shell, i), params, i);
    }
    return EXIT_SUCCESS_TECH;
}

static
int print_help(void)
{
    printf("Usage: history [-hTrSL] (n).\n");
    return EXIT_SUCCESS_TECH;
}

static
int compute_hist(shell_t *shell, history_params_t *params)
{
    switch (params->mode) {
        case SAVE:
            return write_hist(shell);
        case LOAD:
            return load_history(shell);
        case PRINT:
            return print_hist(shell, params);
    }
    return EXIT_FAILURE_TECH;
}

static
void analyze_params(char const *param, history_params_t *params)
{
    param += 1;
    while (*param != '\0') {
        if (*param == 'S')
            params->mode = SAVE;
        if (*param == 'L')
            params->mode = LOAD;
        if (*param == 'T')
            params->timestamp_as_comment = true;
        if (*param == 'r')
            params->reverse_order = true;
        if (*param == 'h')
            params->hiding_ln = true;
        param += 1;
    }
}

int execute_history(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv)
{
    history_params_t params = {
            .mode = PRINT,
    };

    if (argc >= 2 && argv[1] != NULL && strcmp(argv[1], "--help") == 0)
        return print_help();
    for (int i = 1; i < argc; i += 1) {
        if (strncmp(argv[i], "-", 1) == 0) {
            analyze_params(argv[i], &params);
            continue;
        }
        if (params.nb_lignes_to_print != 0)
            return EXIT_FAILURE_TECH;
        params.nb_lignes_to_print = strtoimax(argv[i], NULL, 10);
    }
    return compute_hist(shell, &params);
}
