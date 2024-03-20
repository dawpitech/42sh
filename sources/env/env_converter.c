/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** env_converter header
*/

#include "minishell.h"
#include "my.h"
#include "my_printf.h"

static
char *format_env_var(env_var_t *env_var)
{
    char *rst;
    size_t size_to_alloc;

    if (env_var == NULL || env_var->key == NULL)
        return NULL;
    if (env_var->value != NULL)
        size_to_alloc = sizeof(char) * (my_strlen(env_var->value)
            + my_strlen(env_var->key) + 3);
    else
        size_to_alloc = sizeof(char) * (my_strlen(env_var->key) + 2);
    rst = malloc(size_to_alloc);
    my_strcpy(rst, env_var->key);
    my_strcat(rst, "=");
    if (env_var->value != NULL)
        my_strcat(rst, env_var->value);
    return rst;
}

char **get_env_array(shell_t *shell)
{
    char **env = malloc(sizeof(char *) * (shell->nb_env_var + 1));
    env_var_t *curr = shell->env_vars;

    if (env == NULL)
        return NULL;
    for (int i = 0; i < shell->nb_env_var; i += 1) {
        env[i] = format_env_var(curr);
        curr = curr->next;
    }
    env[shell->nb_env_var] = NULL;
    return env;
}

void free_env_array(char **array)
{
    for (int i = 0; array[i] != NULL; i += 1)
        free(array[i]);
    free(array);
}
