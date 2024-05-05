/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** minishell header
*/

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "minishell.h"

static
int initialize_shell(shell_t *shell, char **env)
{
    if (parse_env_var(shell, env) == RET_ERROR)
        return RET_ERROR;
    shell->running = true;
    shell->isatty = isatty(STDIN_FILENO);
    shell->current_path = getcwd(NULL, 0);
    shell->last_path = NULL;
    shell->last_exit_code = 0;
    load_history(shell);
    return RET_VALID;
}

static
void free_prompt(prompt_t *prompt)
{
    if (prompt->raw_input != NULL)
        free(prompt->raw_input);
    free(prompt);
}

static
void exiting_hook(shell_t *shell)
{
    free(shell->current_path);
    free_prompt(shell->prompt);
    if (shell->last_path != NULL)
        free(shell->last_path);
    free_env_vars(shell);
    history_free(shell);
}

void handle_ctrl_c(int signal)
{
    (void) signal;
    printf("%s", "\n\033[34m?\033[39m> ");
}

int minishell(__attribute__((unused)) int argc,
    __attribute__((unused)) char **argv, char **env)
{
    shell_t shell = {0};

    signal(SIGINT, handle_ctrl_c);
    if (initialize_shell(&shell, env) != EXIT_SUCCESS_TECH)
        return EXIT_FAILURE_TECH;
    while (shell.running) {
        if (present_prompt(&shell) == RET_ERROR)
            break;
        shell.root = parse_input(shell.prompt->raw_input, &shell);
        if (shell.root == NULL) {
            shell.cmds_valid = false;
            shell.last_exit_code = 1;
        }
        if (shell.cmds_valid)
            shell.last_exit_code = compute_root(shell.root);
        history_add(&shell, shell.prompt->raw_input);
        free_parser(shell.root);
    }
    exiting_hook(&shell);
    return shell.running ? EXIT_FAILURE_TECH : shell.last_exit_code;
}
