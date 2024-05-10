/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** prompt navigation
*/

#include <stdio.h>
#include "minishell.h"

void history_up(shell_t *shell)
{
    history_entry_t *entry = NULL;

    if (shell->prompt->history_pos > 0)
        shell->prompt->history_pos -= 1;
    entry = history_get(shell, shell->prompt->history_pos);
    if (entry != NULL) {
        strcpy(shell->prompt->input, entry->line);
        shell->prompt->cursor_pos = (int)strlen(shell->prompt->input);
        shell->prompt->len = shell->prompt->cursor_pos;
        printf("\033[2K\r");
        print_prompt(shell);
        printf("%s", shell->prompt->input);
    }
}

void history_down(shell_t *shell)
{
    history_entry_t *entry = NULL;

    if (shell->prompt->history_pos < (int) shell->history_size - 1)
        shell->prompt->history_pos += 1;
    entry = history_get(shell, shell->prompt->history_pos);
    if (entry != NULL) {
        strcpy(shell->prompt->input, entry->line);
        shell->prompt->cursor_pos = (int) strlen(shell->prompt->input);
        shell->prompt->len = shell->prompt->cursor_pos;
        printf("\033[2K\r");
        print_prompt(shell);
        printf("%s", shell->prompt->input);
    }
}

void cursor_left(shell_t *shell)
{
    if (shell->prompt->cursor_pos <= 0)
        return;
    printf("\033[D");
    shell->prompt->cursor_pos -= 1;
}

void cursor_right(shell_t *shell)
{
    if (shell->prompt->cursor_pos >= (int) strlen(shell->prompt->input))
        return;
    printf("\033[C");
    shell->prompt->cursor_pos += 1;
}
