/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** my_parser header
*/

#include <string.h>

#include "my_parser.h"
#include "builtins.h"
#include "mem_toolbox.h"
#include "my.h"

static
char **parse_args(char *input)
{
    int nb_of_args = 1;
    char *arg = my_strdup(strtok(input, " \t"));
    char **args = malloc(sizeof(char *) * nb_of_args);

    do {
        args = my_realloc(args, sizeof(char *) * (nb_of_args + 1),
            sizeof(char *) * (nb_of_args));
        args[nb_of_args - 1] = arg;
        nb_of_args += 1;
        arg = my_strdup(strtok(NULL, " \t"));
    } while (arg != NULL);
    args[nb_of_args - 1] = NULL;
    return args;
}

static
int init_parser(shell_t *shell, char *input)
{
    int argc;

    shell->prompt->argv = parse_args(input);
    if (shell->prompt->argv == NULL || shell->prompt->argv[0] == NULL) {
        free(shell->prompt->argv);
        return shell->prompt->argv == NULL ? RET_ERROR : RET_VALID;
    }
    for (argc = 0; shell->prompt->argv[argc] != NULL; argc += 1);
    shell->prompt->argc = argc;
    return RET_VALID;
}

int parse_input(shell_t *shell)
{
    if (init_parser(shell, shell->prompt->raw_input) == RET_ERROR)
        return RET_ERROR;
    return RET_VALID;
}
