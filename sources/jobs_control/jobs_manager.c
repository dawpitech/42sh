/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** jobs_manager header
*/

#include "minishell.h"

jobs_t *new_job(shell_t *shell)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (shell->process[i] == NULL) {
            shell->process[i] = malloc(sizeof(jobs_t));
            shell->process[i]->id = i + 1;
            return shell->process[i];
        }
    }
    return NULL;
}

jobs_t *get_job_from_pid(shell_t *shell, int pid)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (shell->process[i] != NULL && shell->process[i]->pid == pid)
            return shell->process[i];
    }
    return NULL;
}
