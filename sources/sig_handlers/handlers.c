/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** handlers header
*/

#include <stdio.h>
#include <wait.h>

#include "minishell.h"

void handle_ctrl_c(__attribute__((unused)) int signal)
{
    printf("\n");
    present_prompt(get_unique_shell());
}

void handle_ctrl_z(__attribute__((unused)) int signal)
{
    printf("\a");
}

void handle_sig_child(int signal)
{
    pid_t pid;
    int child_status;

    while (true) {
        pid = wait(&child_status);
        if (pid == -1) {
            return;
        } else {
            jobs_t *job = get_job_from_pid(get_unique_shell(), pid);
            if (job == NULL)
                return;
            job->state = DONE;
        }
    }
}
