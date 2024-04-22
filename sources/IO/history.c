/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** history header
*/

#include <time.h>
#include <string.h>

#include "minishell.h"
#include "my.h"

void history_add(shell_t *shell, char const *line)
{
    shell->history_size += 1;
    shell->history_entries = realloc(shell->history_entries, sizeof(history_entry_t *)
                                                             * shell->history_size);
    shell->history_entries[shell->history_size - 1] = malloc(sizeof(history_entry_t));
    shell->history_entries[shell->history_size - 1]->line = my_strdup(line);
    shell->history_entries[shell->history_size - 1]->timestamp = time(NULL);
}

history_entry_t *history_get(shell_t *shell, int index)
{
    if (shell->history_entries == NULL)
        return NULL;
    if (index < 0 || index >= (int) shell->history_size)
        return NULL;
    return shell->history_entries[index];
}

void history_free(shell_t *shell)
{
    if (shell->history_entries == NULL)
        return;
    for (int i = 0; i < (int) shell->history_size; i += 1) {
        free(shell->history_entries[i]->line);
        free(shell->history_entries[i]);
    }
    free(shell->history_entries);
}
