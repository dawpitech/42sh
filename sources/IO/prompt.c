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
char *get_from_stdin(int *cursor_pos, shell_t *shell)
{
    struct termios old_config;
    struct termios new_config;
    int c = 0;
    size_t len = 0;
    char *input = NULL;

    input = calloc(1, sizeof(char) * 4096);
    tcgetattr(STDIN_FILENO, &old_config);
    new_config = old_config;
    new_config.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_config);
    do {
        c = getchar();
        if (c == '\n')
            break;
        if (c == 127) {
            if (strlen(input) > 0) {
                memmove(&input[*cursor_pos - 1], &input[*cursor_pos],
                        strlen(input) - *cursor_pos + 1);
                write(STDOUT_FILENO, "\033[2K", 4);
                write(STDOUT_FILENO, "\r> ", 3);
                write(STDOUT_FILENO, input, len);
                for (int i = 0; i < (int)len - *cursor_pos; i += 1)
                    write(STDOUT_FILENO, "\033[D", 3);
                *cursor_pos -= 1;
                len -= 1;
            }
            continue;
        }
        if (c == 27) {
            (void)!getchar();
            c = getchar();
            switch (c) {
                case 'D':
                    if (*cursor_pos <= 0)
                        break;
                    write(STDOUT_FILENO, "\033[D", 3);
                    *cursor_pos -= 1;
                    break;
                case 'C':
                    if (*cursor_pos >= (int)strlen(input))
                        break;
                    write(STDOUT_FILENO, "\033[C", 3);
                    *cursor_pos += 1;
                    break;
                default:
                    break;
            }
            continue;
        }
        input = realloc(input, len + 2);
        memmove(&input[*cursor_pos + 1], &input[*cursor_pos],
                len - *cursor_pos);
        input[*cursor_pos] = (char)c;
        len += 1;
        *cursor_pos += 1;
        write(STDOUT_FILENO, "\033[2K", 4);
        write(STDOUT_FILENO, "\r> ", 3);
        write(STDOUT_FILENO, input, len);
        for (int i = 0; i < (int)len - *cursor_pos; i += 1)
            write(STDOUT_FILENO, "\033[D", 3);
    } while (1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_config);
    printf("\n");
    return input;
}

int present_prompt(shell_t *shell)
{
    int cursor_pos = 0;

    shell->cmds_valid = true;
    shell->prompt = malloc(sizeof(prompt_t));
    shell->prompt->commands = malloc(sizeof(sh_command_t));
    shell->prompt->nb_commands = 0;
    if (shell->prompt == NULL)
        return RET_ERROR;
    print_prompt(shell);
    shell->prompt->raw_input = get_from_stdin(&cursor_pos, shell);
//    if (shell->prompt->raw_input != NULL) {
//            free(shell->prompt->raw_input);
//            shell->prompt->raw_input = NULL;
//    }
    if (shell->prompt->raw_input != NULL)
        return RET_VALID;
    shell->running = false;
    free(shell->prompt);
    return RET_ERROR;
}
