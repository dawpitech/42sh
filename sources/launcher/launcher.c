/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** launcher header
*/

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "launcher.h"
#include "env_converter.h"
#include "my.h"
#include "my_printf.h"
#include "path_explorer.h"
#include "my_put_stderr.h"

int launch_bin(shell_t *shell)
{
    int argc = shell->prompt->argc;
    char **argv = shell->prompt->argv;

    if (my_strstr(argv[0], "/"))
        return launch_bin_by_path(shell, argc, argv);
    return launch_bin_by_env_path(shell, argc, argv);
}

int launch_bin_by_env_path(shell_t *shell, int argc, char **argv)
{
    char *full_path;
    char *bin_loc = search_bin(shell);
    int rt_value;

    if (bin_loc == NULL)
        return RET_ERROR;
    full_path = malloc(sizeof(char) * (my_strlen(bin_loc)
        + my_strlen(argv[0]) + 2));
    if (full_path == NULL)
        return RET_ERROR;
    my_strcpy(full_path, bin_loc);
    my_strcat(full_path, "/");
    my_strcat(full_path, argv[0]);
    argv[0] = full_path;
    rt_value = launch_bin_by_path(shell, argc, argv);
    free(bin_loc);
    return rt_value;
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

int launch_bin_by_path(shell_t *shell, __attribute__((unused)) int argc,
    char **argv)
{
    pid_t pid;
    char **env;
    int child_status;
    int rt_value;

    env = get_env_array(shell);
    pid = fork();
    if (pid == 0) {
        execve(argv[0], argv, env);
        print_error_with_input(argv[0]);
        exit(1);
    }
    waitpid(pid, &child_status, 0);
    rt_value = compute_return_code(child_status);
    free_env_array(env);
    return rt_value;
}
