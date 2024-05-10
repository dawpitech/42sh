/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** prompt_no_tty header
*/

#include <stdio.h>

#include "minishell.h"

char *get_from_stdin_no_tty(void)
{
    char *line = NULL;
    size_t buff_value = 0;
    int rt_value;

    rt_value = (int) getline(&line, &buff_value, stdin);
    if (rt_value <= 0) {
        free(line);
        return NULL;
    }
    line[strlen(line) - 1] = '\0';
    return line;
}
