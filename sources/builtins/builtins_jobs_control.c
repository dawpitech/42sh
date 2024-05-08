/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** builtins_jobs_control header
*/

#include <stdio.h>
#include "minishell.h"
#include "builtins_cmd.h"
#include "utils.h"

int execute_jobs(shell_t *shell, int argc,
    __attribute__((unused)) char **argv)
{
    bool extended_infos = false;

    if (argc == 2)
        extended_infos = true;
    if (argc < 1 || argc > 2) {
        my_put_stderr("jobs: Too many arguments.\n");
        return EXIT_FAILURE_TECH;
    }
    for (int i = 0; i < MAX_JOBS; i++)
        print_job(shell->process[i], extended_infos, true);
    return EXIT_SUCCESS_TECH;
}

int execute_fg(shell_t *shell, int argc, char **argv)
{
    if (argc == 1) {

    } else {
        return EXIT_FAILURE_TECH
    }
}
