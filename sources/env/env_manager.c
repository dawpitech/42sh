/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** env_manager header
*/

#include <stddef.h>
#include <string.h>

#include "minishell.h"

static
void mov_ptr_to_delete(env_var_t *prev, env_var_t *curr, shell_t *context)
{
    if (prev != NULL)
        prev->next = curr->next;
    else
        context->env_vars = curr->next;
}

env_var_t *get_env_var(shell_t *context, char *key)
{
    env_var_t *curr = context->env_vars;

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

int add_env_var(shell_t *context, char *key, char *value)
{
    env_var_t **last = &context->env_vars;
    env_var_t *new = malloc(sizeof(env_var_t));

    if (new == NULL)
        return EXIT_FAILURE_TECH;
    new->key = strdup(key);
    new->value = strdup(value);
    new->next = NULL;
    context->nb_env_var += 1;
    if (*last == NULL) {
        *last = new;
        return EXIT_SUCCESS_TECH;
    }
    while ((*last)->next != NULL)
        last = &(*last)->next;
    (*last)->next = new;
    return EXIT_SUCCESS_TECH;
}

int remove_env_var(shell_t *context, char *key)
{
    env_var_t *prev = NULL;
    env_var_t *curr = context->env_vars;
    bool is_remove = false;

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            mov_ptr_to_delete(prev, curr, context);
            free(curr);
            is_remove = true;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (is_remove)
        context->nb_env_var -= 1;
    return is_remove ? RET_VALID : RET_ERROR;
}

int parse_env_var(shell_t *context, char **env)
{
    char *current_str;
    char *key;
    char *value;

    for (int i = 0; env[i] != NULL; i += 1) {
        current_str = strdup(env[i]);
        key = strtok(current_str, "=");
        value = strtok(NULL, "=");
        if (add_env_var(context, key, value) == EXIT_FAILURE_TECH)
            return EXIT_FAILURE_TECH;
        free(current_str);
    }
    return EXIT_SUCCESS_TECH;
}

void free_env_vars(shell_t *context)
{
    env_var_t *curr = context->env_vars;
    env_var_t *prev = NULL;

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev->value);
        free(prev->key);
        free(prev);
    }
    context->nb_env_var = -1;
}
