/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** my_parser header
*/

#include <stdio.h>

#include "builtins.h"
#include "my.h"
#include "lexer.h"

/*
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
}*/

int parse_input(shell_t *shell)
{
    char *const input = "echo \"bob\"; echo alice";
    lexer_t lexer = lexer_new(input, my_strlen(input));

    printf("Input: %s\n\n", input);
    token_t token = lexer_next(&lexer);
    while (token.kind != TOKEN_END) {
        printf("%.*s (%s)\n", (int) token.text_len, token.text, get_token_kind_as_str(token.kind));
        if (token.kind != TOKEN_INVALID)
            return RET_ERROR;
        token = lexer_next(&lexer);
    }
    return RET_VALID;
}
