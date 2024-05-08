/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** jobs_manager header
*/

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "minishell.h"

static
char *get_state_as_str(int state)
{
    switch (state) {
        case RUNNING:
            return "Running";
        case SUSPENDED:
            return "Suspended";
        case CONTINUED:
            return "Continued";
        case DONE:
            return "Done";
        case KILLED:
            return "Killed";
        default:
            return "NOT IMPLEMENTED";
    }
}

static
void update_job_status(jobs_t *job, int status)
{
    if (WIFSTOPPED(status)) {
        job->state = SUSPENDED;
        return;
    }
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGCONT)
            job->state = CONTINUED;
        if (WTERMSIG(status) == SIGKILL)
            job->state = KILLED;
        return;
    }
    if (WIFEXITED(status)) {
        job->state = DONE;
        return;
    }
}

static
void lookup_child(jobs_t **job)
{
    int child_status;
    int rt = waitpid((*job)->pid, &child_status, WNOHANG | WUNTRACED | WCONTINUED);

    //printf("Waitpid reported %d for process %d and return value is %d\n", child_status, (*job)->pid, rt);
    if (rt == (*job)->pid)
        (*job)->state = DONE;
    if (child_status > 0)
        update_job_status(*job, child_status);
    if ((*job)->state == DONE)
        remove_job(job, true);
}

static
void update_job_priorities(shell_t *shell)
{
    char priority = '+';

    for (int i = MAX_JOBS - 1; i >= 0; i--) {
        if (shell->process[i] == NULL)
            continue;
        shell->process[i]->priority = priority;
        if (priority == '-')
            priority = ' ';
        if (priority == '+')
            priority = '-';
    }
}

void update_childs(shell_t *shell)
{
    for (int i = 0; i < MAX_JOBS; i++)
        if (shell->process[i] != NULL)
            lookup_child(&shell->process[i]);
    update_job_priorities(shell);
}

void print_job(jobs_t *job, bool extended_infos, bool show_priority)
{
    char priority;

    if (job == NULL)
        return;
    priority = (show_priority) ? job->priority : ' ';
    if (extended_infos) {
        printf("[%d]  %c   %d\t%s\t\t\t\t", job->id, priority, job->pid,
               get_state_as_str(job->state));
    } else {
        printf("[%d]  %c %s\t\t\t\t", job->id, priority,
               get_state_as_str(job->state));
    }
    for (int j = 0; j < job->argc; j++) {
        if (j != 0)
            printf(" ");
        printf("%s", job->argv[j]);
    }
    printf("\n");
}

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

int put_job_to_foreground(jobs_t *job)
{
    if (job->state == DONE)
        return RET_ERROR;
    tcsetpgrp(STDIN_FILENO, job->pid);
    kill(job->pid, SIGCONT);
    return wait_after_launch_process(job->pid, NULL);
}

jobs_t *new_job(shell_t *shell)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (shell->process[i] == NULL) {
            shell->process[i] = calloc(1, sizeof(jobs_t));
            shell->process[i]->id = i + 1;
            shell->process[i]->priority = '?';
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
