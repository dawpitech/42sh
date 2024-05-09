/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** run_builtins header
*/

#include <unistd.h>

#include "minishell.h"
#include "builtins.h"

static
int run_builtins(commands_t *cmd, int (fptr)(shell_t *, int, char **))
{
    int rt_value = NO_CMD_FOUND;
    int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);

    if (cmd->fd_in != STDIN_FILENO) {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
    if (cmd->fd_out != STDOUT_FILENO) {
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out);
    }
    rt_value = fptr(cmd->shell, cmd->argc, cmd->argv);
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    return rt_value;
}

int search_and_run_builtins(commands_t *cmd)
{
    for (int i = 0; builtins_list[i].cmd != NULL; i += 1)
        if (strcmp(builtins_list[i].cmd, cmd->argv[0]) == 0)
            return run_builtins(cmd, builtins_list[i].fptr);
    return NO_CMD_FOUND;
}
