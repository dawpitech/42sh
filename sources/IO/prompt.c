/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** prompt header
*/

#include <malloc.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "minishell.h"
#include "my.h"
#include "my_printf.h"

static
void print_prompt(shell_t *shell)
{
    char *color = shell->last_exit_code != 0 ? "\033[91m" : "\033[92m";

    if (!shell->isatty)
        return;
    my_putstr(color);
    my_printf("%d\033[39m> ", shell->last_exit_code);
}

static
char *get_from_stdin(void)
{
    struct termios new_config;
    struct termios old_config;
    char *input;
    int c;

    input = calloc(1, sizeof(char) * 4096);
    tcgetattr(STDIN_FILENO, &old_config);
    new_config = old_config;
    new_config.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_config);
    printf("\033[6 q"); 
    do {
        c = getchar();
        if (c == '\n')
            break;
        if (c == 127) {
            if (strlen(input) > 0) {
                input[strlen(input) - 1] = '\0';
                write(STDOUT_FILENO, "\033[D", 3);
                write(STDOUT_FILENO, "\033[K", 3);
                write(STDOUT_FILENO, " ", 1);
                write(STDOUT_FILENO, "\033[D", 3);
            }
            continue;
        }
        if (c == 27) {
            (void) !getchar();
            c = getchar();
            switch (c) {
                case 'D':
                    write(STDOUT_FILENO, "\033[D", 3);
                    break;
                case 'C':
                    write(STDOUT_FILENO, "\033[C", 3);
                    break;
                default:
                    fprintf(stderr, "%c - %d\n", c, c);
                    break;
            }
            continue;
        }
        write(STDOUT_FILENO, &c, 1);
        input[strlen(input)] = (char) c;
        input[strlen(input) + 1] = '\0';
    } while (true);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_config);
    printf("\n");
    return input;
}

int present_prompt(shell_t *shell)
{
    shell->cmds_valid = true;
    shell->prompt = malloc(sizeof(prompt_t));
    shell->prompt->commands = malloc(sizeof(sh_command_t));
    shell->prompt->nb_commands = 0;
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
