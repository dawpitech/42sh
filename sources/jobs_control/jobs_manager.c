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
            shell->process[i]->id = i;
            return shell->process[i];
        }
    }
    return NULL;
}
