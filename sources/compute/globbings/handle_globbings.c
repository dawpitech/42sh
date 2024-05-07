/*
** EPITECH PROJECT, 2024
** globbings
** File description:
** handle_globbings
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <glob.h>

#include "minishell.h"

static
char **realloc_tab(commands_t *cmd, int folder_size)
{
    if (!cmd->argv)
        return NULL;
    cmd->argv = realloc(cmd->argv, sizeof(char *) *
        (folder_size + cmd->argc + 1));
    if (!cmd->argv)
        return NULL;
    for (int i = cmd->argc; i < folder_size + cmd->argc + 1; i ++)
        cmd->argv[i] = NULL;
    return cmd->argv;
}

static
void fill_tab(commands_t *cmd, glob_t *glob_result, int *i)
{
    if (cmd->argv[*i + 1] != NULL) {
        cmd->argv[(*glob_result).gl_pathc + cmd->argc - 2] = strdup(cmd->\
        argv[*i + 1]);
        free(cmd->argv[*i + 1]);
    }
    free(cmd->argv[*i]);
    cmd->argv[*i] = NULL;
    for (size_t j = 0; (*glob_result).gl_pathc > j; j++) {
        cmd->argv[*i] = strdup((*glob_result).gl_pathv[j]);
        (*i)++;
    }
    (*i)--;
}

static
int globbing_asterisque(commands_t *cmd, glob_t glob_result, int *i)
{
    if (strstr(cmd->argv[*i], "*") != NULL) {
        if (glob(cmd->\
        argv[*i], GLOB_TILDE, NULL, &glob_result) == GLOB_NOMATCH)
            return dprintf(2, "%s: No match.\n", cmd->argv[0]);
        cmd->argv = realloc_tab(cmd, glob_result.gl_pathc);
        if (!cmd->argv)
            return RET_ERROR;
        fill_tab(cmd, &glob_result, i);
        cmd->argc += glob_result.gl_pathc - 1;
        globfree(&glob_result);
        cmd->argv[cmd->argc] = NULL;
    }
    return RET_VALID;
}

char **handle_globbings(commands_t *cmd)
{
    glob_t glob_result = {0};

    for (int i = 0; cmd->argv[i]; i ++) {
        if (globbing_asterisque(cmd, glob_result, &i) != RET_VALID)
            return NULL;
        if (!cmd->argv)
            return NULL;
    }
    return cmd->argv;
}
