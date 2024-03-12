/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** env_manager header
*/

#ifndef MINISHELL_ENV_MANAGER_H
    #define MINISHELL_ENV_MANAGER_H
    #include "minishell.h"
env_var_t *get_env_var(shell_t *context, char *key);
int add_env_var(shell_t *context, char *key, char *value);
int parse_env_var(shell_t *context, char **env);
void free_env_var(shell_t *context);
int remove_env_var(shell_t *context, char *key);
#endif //MINISHELL_ENV_MANAGER_H
