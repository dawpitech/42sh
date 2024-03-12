/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** builtins_runner header
*/

#include "../../include/builtins_runner.h"
#include "../../include/builtins.h"
#include "../../include/my.h"

int search_and_run_builtins(shell_t *shell, char *command)
{
    for (int i = 0; builtins_list[i].cmd != NULL; i += 1) {
        if (my_strcmp(builtins_list[i].cmd, command) == 0) {
            return builtins_list[i].fptr(shell, shell->prompt->argc,
                shell->prompt->argv);
        }
    }
    return NO_CMD_FOUND;
}
