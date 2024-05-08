/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** builtins_jobs_control header
*/

#include <stdio.h>
#include <unistd.h>

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

static
jobs_t *get_last_job(shell_t *shell)
{
    for (int i = MAX_JOBS - 1; i >= 0; i--) {
        if (shell->process[i] == NULL)
            continue;
        return shell->process[i];
    }
    return NULL;
}

int execute_fg(shell_t *shell, int argc, __attribute__((unused)) char **argv)
{
    jobs_t *job;

    if (argc == 1) {
        job = get_last_job(shell);

        if (job == NULL) {
            my_put_stderr("fg: No current job.\n");
            return EXIT_FAILURE_TECH;
        }
        printf("%s\n", job->argv[0]);
        put_job_to_foreground(job);
        return EXIT_SUCCESS_TECH;
    }
    return EXIT_FAILURE_TECH;
}
