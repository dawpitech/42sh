/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** exit_cmd header
*/

#ifndef MINISHELL_BUILTINS_CMD_H
    #define MINISHELL_BUILTINS_CMD_H
    #include "minishell.h"
int execute_cd(shell_t *shell, __attribute__((unused)) int argc, char **argv);
int execute_exit(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv);
int execute_env(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv);
int execute_setenv(shell_t *shell, int argc, char **argv);
int execute_unsetenv(shell_t *shell, int argc, char **argv);
int execute_history(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv);
int execute_search_history(shell_t *shell, __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv);
int execute_jobs(shell_t *shell, int argc,
    __attribute__((unused)) char **argv);
int execute_fg(shell_t *shell, int argc, __attribute__((unused)) char **argv);
#endif //MINISHELL_BUILTINS_CMD_H
