/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** my_parser header
*/

#include <stdio.h>
#include <unistd.h>

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
void initialize_cmd(sh_command_t *cmd)
{
    cmd->argc = 0;
    cmd->argv = NULL;
    cmd->type = EXPR;
    cmd->stdin_file = NULL;
    cmd->stdout_file = NULL;
    cmd->fd_stdin = STDIN_FILENO;
    cmd->fd_stdout = STDOUT_FILENO;
    cmd->type = EXPR;
}

static
int handle_redirect_file_name(prompt_t *p, token_t *t)
{
    char *file_name = malloc(sizeof(char) * (t->text_len + 1));

    if (p->nb_commands == 0) {
        my_put_stderr("Ratio command.\n");
        return RET_ERROR;
    }
    my_strncpy(file_name, t->text, (int) t->text_len);
    file_name[t->text_len] = '\0';
    p->commands[p->nb_commands - 1].stdout_file = file_name;
    return RET_VALID;
}

static
int handle_symbol(prompt_t *prompt, token_t *token, lexer_t *l)
{
    if (prompt->nb_commands != 0 && (prompt->commands[prompt->nb_commands - 1]
        .type == REDR || prompt->commands[prompt->nb_commands - 1].type ==
        DBL_REDR))
        return handle_redirect_file_name(prompt, token);
    if (!l->is_in_command) {
        prompt->nb_commands += 1;
        prompt->commands = my_realloc(prompt->commands, sizeof(sh_command_t) *
            (prompt->nb_commands + 2), sizeof(sh_command_t) *
            (prompt->nb_commands + 1));
        initialize_cmd(&prompt->commands[prompt->nb_commands - 1]);
        add_arg_to_cmd(&prompt->commands[prompt->nb_commands - 1],
            token->text, token->text_len);
        prompt->commands[prompt->nb_commands] = (sh_command_t){0};
        l->is_in_command = true;
    } else {
        add_arg_to_cmd(&prompt->commands[prompt->nb_commands - 1],
            token->text, token->text_len);
    }
    return RET_VALID;
}

static
int handle_redirect_right(prompt_t *prompt, token_t *token)
{
    if (prompt->nb_commands == 0) {
        my_put_stderr("Invalid null command.\n");
        return RET_ERROR;
    }
    if (token->kind == TOKEN_REDIRECT_R)
        prompt->commands[prompt->nb_commands - 1].type = REDR;
    if (token->kind == TOKEN_REDIRECT_RR)
        prompt->commands[prompt->nb_commands - 1].type = DBL_REDR;
    if (token->kind == TOKEN_REDIRECT_L)
        prompt->commands[prompt->nb_commands - 1].type = REDL;
    if (token->kind == TOKEN_REDIRECT_LL)
        prompt->commands[prompt->nb_commands - 1].type = DBL_REDL;
    return RET_VALID;
}

static
int compute_token(prompt_t *prompt, token_t *token, lexer_t *lexer)
{
    if (token->kind == TOKEN_INVALID)
        return RET_ERROR;
    if (token->kind == TOKEN_REDIRECT_R || token->kind == TOKEN_REDIRECT_RR)
        return handle_redirect_right(prompt, token);
    if (token->kind == TOKEN_SYMBOL)
        return handle_symbol(prompt, token, lexer);
    if (token->kind == TOKEN_SEMICOLON)
        lexer->is_in_command = false;
    return RET_VALID;
}

int parse_input(shell_t *shell)
{
    char *const input = shell->prompt->raw_input;
    lexer_t lexer = lexer_new(input, my_strlen(input));
    token_t token = lexer_next(&lexer);

    while (token.kind != TOKEN_END) {
        if (compute_token(shell->prompt, &token, &lexer) == RET_ERROR)
            return RET_ERROR;
        token = lexer_next(&lexer);
    }
    return RET_VALID;
}
