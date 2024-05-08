/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** builtins header
*/

#ifndef MINISHELL_BUILTINS_H
    #define MINISHELL_BUILTINS_H
    #include <stddef.h>

    #include "builtins_cmd.h"
    #include "minishell.h"
typedef struct {
    char *cmd;
    int (*fptr)(shell_t *context, int argc, char **argv);
} builtin_t;
static const builtin_t builtins_list[] = {
    {.cmd = "env", .fptr = execute_env},
    {.cmd = "exit", .fptr = execute_exit},
    {.cmd = "setenv", .fptr = execute_setenv},
    {.cmd = "unsetenv", .fptr = execute_unsetenv},
    {.cmd = "cd", .fptr = execute_cd},
    {.cmd = "history", .fptr = execute_history},
    {.cmd = "!", .fptr = execute_search_history},
    {.cmd = "jobs", .fptr = execute_jobs},
    {.cmd = NULL, .fptr = NULL},
};
#endif //MINISHELL_BUILTINS_H
