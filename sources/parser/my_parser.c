/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** my_parser header
*/

#include "builtins.h"
#include "my.h"
#include "lexer.h"
#include "utils.h"

static
void add_arg_to_cmd(sh_command_t *cmd, char const *arg, size_t arg_len)
{
    char *arg_cpy = malloc(sizeof(char) * (arg_len + 1));

    cmd->argv = my_realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2),
        sizeof(char *) * (cmd->argc + 1));
    my_strncpy(arg_cpy, arg, (int) arg_len);
    arg_cpy[arg_len] = '\0';
    cmd->argv[cmd->argc] = arg_cpy;
    cmd->argv[cmd->argc + 1] = NULL;
    cmd->argc += 1;
}

static
void handle_symbol(prompt_t *prompt, token_t token, bool *is_in_command)
{
    if (!*is_in_command) {
        prompt->nb_commands += 1;
        prompt->commands = my_realloc(prompt->commands, sizeof(sh_command_t) *
            (prompt->nb_commands + 2), sizeof(sh_command_t) *
            (prompt->nb_commands + 1));
        prompt->commands[prompt->nb_commands - 1].argc = 0;
        prompt->commands[prompt->nb_commands - 1].argv = NULL;
        add_arg_to_cmd(&prompt->commands[prompt->nb_commands - 1],
            token.text, token.text_len);
        prompt->commands[prompt->nb_commands] = (sh_command_t){0};
        *is_in_command = true;
    } else {
        add_arg_to_cmd(&prompt->commands[prompt->nb_commands - 1],
            token.text, token.text_len);
    }
}

int parse_input(shell_t *shell)
{
    char *const input = shell->prompt->raw_input;
    lexer_t lexer = lexer_new(input, my_strlen(input));
    bool is_in_command = false;
    token_t token = lexer_next(&lexer);

    while (token.kind != TOKEN_END) {
        if (token.kind == TOKEN_INVALID)
            return RET_ERROR;
        if (token.kind == TOKEN_SYMBOL) {
            handle_symbol(shell->prompt, token, &is_in_command);
        } else {
            is_in_command = false;
        }
        token = lexer_next(&lexer);
    }
    return RET_VALID;
}
