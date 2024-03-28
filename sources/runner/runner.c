/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** runner header
*/

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

#include "builtins.h"
#include "utils.h"
#include "my.h"
#include "path_explorer.h"

static
int run_builtins(shell_t *shell, sh_command_t *cmd,
    int (fptr)(shell_t *, int, char **))
{
    int rt_value = NO_CMD_FOUND;
    int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);

    if (cmd->fd_stdin != STDIN_FILENO) {
        dup2(cmd->fd_stdin, STDIN_FILENO);
        close(cmd->fd_stdin);
    }
    if (cmd->fd_stdout != STDOUT_FILENO) {
        dup2(cmd->fd_stdout, STDOUT_FILENO);
        close(cmd->fd_stdout);
    }
    rt_value = fptr(shell, cmd->argc, cmd->argv);
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    return rt_value;
}

static
int search_and_run_builtins(shell_t *shell, sh_command_t *cmd)
{
    for (int i = 0; builtins_list[i].cmd != NULL; i += 1)
        if (my_strcmp(builtins_list[i].cmd, cmd->argv[0]) == 0)
            return run_builtins(shell, cmd, builtins_list[i].fptr);
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
void handle_redirect_r(sh_command_t *cmd)
{
    int fd;
    int oflag;

    if (cmd->type == REDR)
        oflag = O_WRONLY | O_CREAT | O_TRUNC;
    else
        oflag = O_WRONLY | O_CREAT | O_APPEND;
    if (cmd->stdout_file == NULL)
        my_put_stderr("Missing name for redirect.\n");
    fd = open(cmd->stdout_file, oflag, 0644);
    if (fd == -1)
        exit(1);
    cmd->fd_stdout = fd;
}

static
void handle_redirect_l(sh_command_t *cmd)
{
    int fd;

    if (cmd->type == DBL_REDL)
        return;
    if (cmd->stdin_file == NULL)
        my_put_stderr("Missing name for redirect.\n");
    fd = open(cmd->stdin_file, O_RDONLY);
    if (fd == -1)
        exit(1);
    cmd->fd_stdin = fd;
}

static
void child_process(shell_t *shell, sh_command_t *cmd)
{
    char **env = get_env_array(shell);

    if (cmd->type == REDR || cmd->type == DBL_REDR)
        handle_redirect_r(cmd);
    if (cmd->type == REDL || cmd->type == DBL_REDL)
        handle_redirect_l(cmd);
    if (cmd->fd_stdin != STDIN_FILENO) {
        dup2(cmd->fd_stdin, STDIN_FILENO);
        close(cmd->fd_stdin);
    }
    if (cmd->fd_stdout != STDOUT_FILENO) {
        dup2(cmd->fd_stdout, STDOUT_FILENO);
        close(cmd->fd_stdout);
    }
    execve(cmd->argv[0], cmd->argv, env);
    print_error_with_input(cmd->argv[0]);
    exit(1);
}

static
int launch_bin(shell_t *shell, sh_command_t *cmd)
{
    pid_t pid;
    int child_status;

    pid = fork();
    if (pid == 0)
        child_process(shell, cmd);
    if (cmd->fd_stdin != STDIN_FILENO)
        close(cmd->fd_stdin);
    if (cmd->fd_stdout != STDOUT_FILENO)
        close(cmd->fd_stdout);
    if (cmd->type == PIPE)
        return 0;
    waitpid(pid, &child_status, 0);
    return compute_return_code(child_status);
}

static
int resolve_path(shell_t *shell, sh_command_t *cmd)
{
    char *full_path;
    char *bin_location = search_bin(shell, cmd);

    if (bin_location == NULL)
        return NO_CMD_FOUND;
    full_path = malloc(sizeof(char) * (my_strlen(bin_location)
        + my_strlen(cmd->argv[0]) + 2));
    if (full_path == NULL)
        exit(EXIT_FAILURE_TECH);
    my_strcpy(full_path, bin_location);
    my_strcat(full_path, "/");
    my_strcat(full_path, cmd->argv[0]);
    free(cmd->argv[0]);
    cmd->argv[0] = full_path;
    return RET_VALID;
}

int run_command(shell_t *shell, sh_command_t *cmd)
{
    int return_value;

    return_value = search_and_run_builtins(shell, cmd);
    if (return_value != NO_CMD_FOUND)
        return return_value;
    if (!my_strstr(cmd->argv[0], "/") && resolve_path(shell, cmd)
        == NO_CMD_FOUND) {
            my_put_stderr(cmd->argv[0]);
            my_put_stderr(": Command not found.\n");
            return 1;
    }
    return_value = launch_bin(shell, cmd);
    return return_value;
}
