/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** prompt header
*/

#include <malloc.h>
#include <stddef.h>

#include "../../include/prompt.h"
#include "../../include/my.h"
#include "../../include/my_parser.h"
#include "my_printf.h"

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
    if (shell->isatty)
        my_printf("%d> $ ", shell->last_exit_code);
    shell->prompt->raw_input = get_from_stdin();
    if (shell->prompt->raw_input != NULL)
        return RET_VALID;
    shell->running = false;
    free(shell->prompt);
    return RET_ERROR;
}
