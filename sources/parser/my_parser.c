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
#include "utils.h"

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

static
void add_arg_to_cmd(sh_command_t *cmd, char const *arg, size_t arg_len)
{
    char *arg_cpy = malloc(sizeof(char) * (arg_len + 1));

    cmd->argv = my_realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2),
        sizeof(char *) * (cmd->argc + 1));
    my_strncpy(arg_cpy, arg, (int) arg_len);
    my_strcat(arg_cpy, "\0");
    cmd->argv[cmd->argc] = arg_cpy;
    cmd->argv[cmd->argc + 1] = NULL;
    cmd->argc += 1;
}

int parse_input(shell_t *shell)
{
    char *const input = shell->prompt->raw_input;
    lexer_t lexer = lexer_new(input, my_strlen(input));

    prompt_t *prompt = shell->prompt;
    bool is_in_command = false;

    printf("Input: %s\n\n", input);
    token_t token = lexer_next(&lexer);
    while (token.kind != TOKEN_END) {
        printf("%.*s (%s)\n", (int) token.text_len, token.text, get_token_kind_as_str(token.kind));
        if (token.kind == TOKEN_INVALID)
            return RET_ERROR;

        if (token.kind == TOKEN_SYMBOL) {
            if (!is_in_command) {
                prompt->nb_commands += 1;
                prompt->commands = my_realloc(prompt->commands, sizeof(sh_command_t) *
                (prompt->nb_commands + 2), sizeof(sh_command_t) *
                (prompt->nb_commands + 1));
                prompt->commands[prompt->nb_commands - 1].argc = 0;
                prompt->commands[prompt->nb_commands - 1].argv = NULL;
                add_arg_to_cmd(&prompt->commands[prompt->nb_commands - 1],
                token.text, token.text_len);
                prompt->commands[prompt->nb_commands] = (sh_command_t){0}; // Null-terminate the commands array
                is_in_command = true;
            } else {
                add_arg_to_cmd(&prompt->commands[prompt->nb_commands - 1],
                token.text, token.text_len);
            }
        } else {
            is_in_command = false;
        }
        token = lexer_next(&lexer);
    }
    for (int i = 0; prompt->commands[i].argv != NULL; i += 1) {
        printf("Command %d\n", i);
        for (int j = 0; prompt->commands[i].argv[j] != NULL; j += 1) {
            printf("Arg %d: %s\n", j, prompt->commands[i].argv[j]);
        }
    }
    return RET_VALID;
}
