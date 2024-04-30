/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** compute_command header
*/

#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include "minishell.h"
#include "utils.h"
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

static
int search_and_run_builtins(commands_t *cmd)
{
    for (int i = 0; builtins_list[i].cmd != NULL; i += 1)
        if (strcmp(builtins_list[i].cmd, cmd->argv[0]) == 0)
            return run_builtins(cmd, builtins_list[i].fptr);
    return NO_CMD_FOUND;
}

static
int compute_return_code(int child_status)
{
    if (WIFSIGNALED(child_status)) {
        my_put_stderr(strsignal(WTERMSIG(child_status)));
        if (WCOREDUMP(child_status))
            my_put_stderr(" (core dumped)");
        my_put_stderr("\n");
        return child_status;
    }
    return WEXITSTATUS(child_status);
}

static
void child_process(commands_t *cmd)
{
    char **env = get_env_array(cmd->shell);

    if (cmd->fd_in != STDIN_FILENO) {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
    if (cmd->fd_out != STDOUT_FILENO) {
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out);
    }
    errno = 0;
    execve(cmd->argv[0], cmd->argv, env);
    print_error_with_input(cmd->argv[0]);
    exit(1);
}

static
int launch_binary(commands_t *cmd)
{
    pid_t pid;
    int child_status;

    pid = fork();
    if (pid == 0)
        child_process(cmd);
    if (cmd->fd_in != STDIN_FILENO)
        close(cmd->fd_in);
    if (cmd->fd_out != STDOUT_FILENO) {
        close(cmd->fd_out);
        return CMD_IS_A_PIPE;
    }
    waitpid(pid, &child_status, 0);
    return compute_return_code(child_status);
}

int compute_cmd(commands_t *cmd)
{
    int return_value;

    return_value = search_and_run_builtins(cmd);
    if (return_value != NO_CMD_FOUND)
        return return_value;

    return 0;
}
