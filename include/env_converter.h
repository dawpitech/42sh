/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** env_converter header
*/

#ifndef MINISHELL_ENV_CONVERTER_H
    #define MINISHELL_ENV_CONVERTER_H
    #include "minishell.h"
char **get_env_array(shell_t *shell);
void free_env_array(char **array);
#endif //MINISHELL_ENV_CONVERTER_H
