/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** prompt header
*/

#include <malloc.h>
#include <stddef.h>

#include "minishell.h"
#include "my.h"
#include "my_printf.h"

static
void print_prompt(shell_t *shell)
{
    char *color = shell->last_exit_code != 0 ? "\\033[91m" : "\\033[92m";
    char static *color_reset = "\\033[39m";
    if (!shell->isatty)
        return;
    if (shell->last_exit_code != 0)
    my_printf("%s%d%s>%c $ ", color, color_reset, shell->last_exit_code);
}

static
char *get_from_stdin(void)
{
    char *line = NULL;
    size_t buff_value = 0;
    int rt_value;

    rt_value = (int) getline(&line, &buff_value, stdin);
    if (rt_value <= 0) {
        free(line);
        return NULL;
    }
    line[my_strlen(line) - 1] = '\0';
    return line;
}

int present_prompt(shell_t *shell)
{
    shell->prompt = malloc(sizeof(prompt_t));
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
