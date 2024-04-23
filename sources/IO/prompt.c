/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** prompt header
*/

#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include "minishell.h"

static
void print_prompt(shell_t *shell)
{
    char *color = shell->last_exit_code != 0 ? "\033[91m" : "\033[92m";

    if (!shell->isatty)
        return;
    printf("%s%d\033[39m> ", color, shell->last_exit_code);
}

static
char *get_from_stdin(void)
{
    char *line = NULL;
    size_t buff_value = 0;
    int rt_value;

    rt_value = (int) getline(&line, &buff_value, stdin);
    if (rt_value <= 0) {
        printf("exit\n");
        free(line);
        return NULL;
    }
    line[strlen(line) - 1] = '\0';
    return line;
}

int present_prompt(shell_t *shell)
{
    shell->cmds_valid = true;
    shell->prompt = malloc(sizeof(prompt_t));
    shell->prompt->commands = malloc(sizeof(sh_command_t));
    shell->prompt->nb_commands = 0;
    if (shell->prompt == NULL)
        return RET_ERROR;
    print_prompt(shell);
    shell->prompt->raw_input = get_from_stdin();
    if (shell->prompt->raw_input != NULL)
        return RET_VALID;
    shell->running = false;
    free(shell->prompt);
    return RET_ERROR;
}
