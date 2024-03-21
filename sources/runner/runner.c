/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** runner header
*/

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "builtins.h"
#include "utils.h"
#include "my.h"
#include "path_explorer.h"

static
int search_and_run_builtins(shell_t *shell, sh_command_t *cmd)
{
    for (int i = 0; builtins_list[i].cmd != NULL; i += 1) {
        if (my_strcmp(builtins_list[i].cmd, cmd->argv[0]) == 0) {
            return builtins_list[i].fptr(shell, cmd->argc, cmd->argv);
        }
    }
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
int launch_bin(shell_t *shell, char **argv)
{
    pid_t pid;
    char **env;
    int child_status;

    env = get_env_array(shell);
    pid = fork();
    if (pid == 0) {
        execve(argv[0], argv, env);
        print_error_with_input(argv[0]);
        exit(1);
    }
    waitpid(pid, &child_status, 0);
    free_env_array(env);
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
    if (!my_strstr(cmd->argv[0], "/"))
        resolve_path(shell, cmd);
    return_value = launch_bin(shell, cmd->argv);
    if (return_value == NO_CMD_FOUND) {
        my_put_stderr(cmd->argv[0]);
        my_put_stderr(": Command not found.\n");
    }
    return return_value;
}
