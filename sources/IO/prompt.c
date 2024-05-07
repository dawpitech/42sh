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
struct termios init_termios(void)
{
    struct termios old_config;
    struct termios new_config;

    tcgetattr(STDIN_FILENO, &old_config);
    new_config = old_config;
    new_config.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_config);
    return old_config;
}

static
void remove_char(shell_t *shell)
{
    if (strlen(shell->prompt->input) > 0) {
        memmove(&shell->prompt->input[shell->prompt->cursor_pos - 1],
                &shell->prompt->input[shell->prompt->cursor_pos],
                strlen(shell->prompt->input) - shell->prompt->cursor_pos + 1);
        write(STDOUT_FILENO, "\033[2K", 4);
        write(STDOUT_FILENO, "\r", 1);
        print_prompt(shell);
        write(STDOUT_FILENO, shell->prompt->input, shell->prompt->len);
        for (int i = 0; i <
        (int)shell->prompt->len - shell->prompt->cursor_pos; i += 1)
            write(STDOUT_FILENO, "\033[D", 3);
        shell->prompt->cursor_pos -= 1;
        shell->prompt->cursor_pos = shell->prompt->cursor_pos;
        shell->prompt->len -= 1;
    }
}

static
void add_char(shell_t *shell)
{
    shell->prompt->input = realloc(shell->prompt->input,
            shell->prompt->len + 2);
    memmove(&shell->prompt->input[shell->prompt->cursor_pos + 1],
            &shell->prompt->input[shell->prompt->cursor_pos],
            shell->prompt->len - shell->prompt->cursor_pos);
    shell->prompt->input[shell->prompt->cursor_pos] = shell->prompt->ch;
    shell->prompt->len += 1;
    shell->prompt->cursor_pos += 1;
    write(STDOUT_FILENO, "\033[2K", 4);
    write(STDOUT_FILENO, "\r", 1);
    print_prompt(shell);
    write(STDOUT_FILENO, shell->prompt->input, shell->prompt->len);
    for (int i = 0;
    i < (int)shell->prompt->len - shell->prompt->cursor_pos; i += 1)
        write(STDOUT_FILENO, "\033[D", 3);
}

static
void handle_arrow_keys(shell_t *shell)
{
    (void)!getchar();
    shell->prompt->ch = (char)getchar();
    switch (shell->prompt->ch) {
        case 'D':
            if (shell->prompt->cursor_pos <= 0)
                break;
            write(STDOUT_FILENO, "\033[D", 3);
            shell->prompt->cursor_pos -= 1;
            break;
        case 'C':
            if (shell->prompt->cursor_pos >= (int)strlen(shell->prompt->input))
                break;
            write(STDOUT_FILENO, "\033[C", 3);
            shell->prompt->cursor_pos += 1;
            break;
        default:
            break;
    }
}

static
char *get_from_stdin(shell_t *shell)
{
    struct termios old_config = init_termios();

    do {
        shell->prompt->ch = (char)getchar();
        if (shell->prompt->ch == '\n')
            break;
        if (shell->prompt->ch == 127) {
            remove_char(shell);
            continue;
        }
        if (shell->prompt->ch == 27) {
            handle_arrow_keys(shell);
            continue;
        }
        add_char(shell);
    } while (1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_config);
    printf("\n");
    return shell->prompt->input;
}

int present_prompt(shell_t *shell)
{
    shell->cmds_valid = true;
    shell->prompt = malloc(sizeof(prompt_t));
    shell->prompt->commands = malloc(sizeof(sh_command_t));
    shell->prompt->nb_commands = 0;
    shell->prompt->input = NULL;
    shell->prompt->cursor_pos = 0;
    shell->prompt->len = 0;
    shell->prompt->ch = 0;
    if (shell->prompt == NULL)
        return RET_ERROR;
    print_prompt(shell);
    shell->prompt->raw_input = get_from_stdin(shell);
    if (shell->prompt->raw_input != NULL)
        return RET_VALID;
    shell->running = false;
    free(shell->prompt);
    return RET_ERROR;
}
