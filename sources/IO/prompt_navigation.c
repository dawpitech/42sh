/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** prompt navigation
*/

#include <stdio.h>
#include "minishell.h"

void history_up(shell_t *shell, char **old_input)
{
    history_entry_t *entry = NULL;

    if (shell->prompt->history_pos > 0) {
        if (!(*old_input))
            *old_input = strdup(shell->prompt->input);
        shell->prompt->history_pos -= 1;
    }
    entry = history_get(shell, shell->prompt->history_pos);
    if (entry != NULL) {
        strcpy(shell->prompt->input, entry->line);
        shell->prompt->cursor_pos = (int)strlen(shell->prompt->input);
        shell->prompt->len = shell->prompt->cursor_pos;
        print_prompt(shell);
        printf("%s", shell->prompt->input);
    }
}

void history_down(shell_t *shell, char **old_input)
{
    history_entry_t *entry = NULL;

    if (shell->prompt->history_pos < (int) shell->history_size)
        shell->prompt->history_pos += 1;
    if (shell->prompt->history_pos == (int) shell->history_size) {
        print_prompt(shell);
        printf(*old_input == NULL ? "" : "%s", *old_input);
        if (*old_input == NULL)
            shell->prompt->input[0] = '\0';
        return;
    }
    entry = history_get(shell, shell->prompt->history_pos);
    if (entry != NULL) {
        strcpy(shell->prompt->input, entry->line);
        shell->prompt->cursor_pos = (int) strlen(shell->prompt->input);
        shell->prompt->len = shell->prompt->cursor_pos;
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
