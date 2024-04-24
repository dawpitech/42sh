/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** history header
*/

#include <time.h>
#include <string.h>
#include <stdio.h>

#include "minishell.h"

void history_add(shell_t *shell, char const *line)
{
    shell->history_size += 1;
    shell->history_entries = realloc(shell->history_entries,
        sizeof(history_entry_t *)* shell->history_size);
    shell->history_entries[shell->history_size - 1] =
        malloc(sizeof(history_entry_t));
    shell->history_entries[shell->history_size - 1]->line = strdup(line);
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

int write_hist(shell_t *shell)
{
    FILE *hist;

    hist = fopen(HISTORY_FILE, "w");
    if (hist == NULL)
        return EXIT_FAILURE_TECH;
    for (int i = 0; i < (int) shell->history_size; i += 1) {
        fprintf(hist, "#+%ld\n", shell->history_entries[i]->timestamp);
        fprintf(hist, "%s\n", shell->history_entries[i]->line);
    }
    fclose(hist);
    return EXIT_SUCCESS_TECH;
}

static
void analyze_line(shell_t *shell, char *line, time_t *timestamp)
{
    if (line[0] == '#') {
        line += 2;
        *timestamp = strtol(line, NULL, 10);
    } else {
        line[strlen(line) - 1] = '\0';
        shell->history_size += 1;
        shell->history_entries = realloc(shell->history_entries,
            sizeof(history_entry_t *) * shell->history_size);
        shell->history_entries[shell->history_size - 1] =
            malloc(sizeof(history_entry_t));
        shell->history_entries[shell->history_size - 1]->line =
            strdup(line);
        shell->history_entries[shell->history_size - 1]->timestamp =
            *timestamp;
    }
}

int load_history(shell_t *shell)
{
    FILE *f_stream;
    char *line = NULL;
    size_t buffer_value = 0;
    time_t timestamp;

    f_stream = fopen(HISTORY_FILE, "r");
    if (f_stream == NULL)
        return EXIT_FAILURE_TECH;
    for (; getline(&line, &buffer_value, f_stream) > 0;)
        analyze_line(shell, line, &timestamp);
    fclose(f_stream);
    return EXIT_SUCCESS_TECH;
}
