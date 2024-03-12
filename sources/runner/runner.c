/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** runner header
*/

#include "../../include/runner.h"
#include "../../include/builtins.h"
#include "../../include/builtins_runner.h"
#include "../../include/launcher.h"
#include "../../include/my_put_stderr.h"

int run_command(shell_t *shell)
{
    int return_value;

    return_value = search_and_run_builtins(shell, shell->prompt->argv[0]);
    if (return_value == NO_CMD_FOUND) {
        return_value = launch_bin(shell);
    } else {
        return return_value;
    }
    if (return_value == RET_ERROR) {
        my_put_stderr(shell->prompt->argv[0]);
        my_put_stderr(": Command not found.\n");
    }
    return return_value != NO_CMD_FOUND ? return_value : EXIT_SUCCESS_TECH;
}
