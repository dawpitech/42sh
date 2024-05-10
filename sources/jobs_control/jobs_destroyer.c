/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** jobs_destroyer header
*/

#include "minishell.h"

void remove_job(jobs_t **job, bool should_print)
{
    int id;

    if (*job == NULL)
        return;
    if (should_print)
        print_job(*job, false, false);
    id = (int) (*job)->id;
    for (int i = 0; i < (*job)->argc; i++)
        free((*job)->argv[i]);
    free((*job)->argv);
    free(*job);
    get_unique_shell()->process[id - 1] = NULL;
}
