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
#include <errno.h>

#include "builtins.h"
#include "utils.h"
#include "my.h"
#include "path_explorer.h"

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
            shell->cmds_valid = false;
            my_put_stderr(cmd->argv[0]);
            my_put_stderr(": Command not found.\n");
            return 1;
    }
    return_value = launch_bin(shell, cmd);
    return return_value;
}
