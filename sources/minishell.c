/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** minishell header
*/

#include <unistd.h>
#include <signal.h>

#include "minishell.h"
#include "my.h"

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
    return RET_VALID;
}

static
void free_prompt(prompt_t *prompt)
{
    free(prompt->raw_input);
    free(prompt->commands->stdin_file);
    free(prompt->commands->stdout_file);
    for (int i = 0; prompt->commands->argv[i] != NULL; i ++)
        free(prompt->commands->argv[i]);
    free(prompt->commands->argv);
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
}

void handle_ctrl_c(int signal)
{
    (void) signal;
    my_putstr("\n\033[34m?\033[39m> ");
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
        if (parse_input(shell.prompt->raw_input) == NULL) {
            shell.cmds_valid = false;
            shell.last_exit_code = 1;
        }
        for (int i = 0; i < shell.prompt->nb_commands &&
            shell.cmds_valid; i += 1)
            shell.last_exit_code = run_command(&shell,
                &shell.prompt->commands[i]);
    }
    exiting_hook(&shell);
    return shell.running ? EXIT_FAILURE_TECH : shell.last_exit_code;
}
