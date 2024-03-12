/*
** EPITECH PROJECT, 2023
** memory_utils
** File description:
** title
*/

#include "include/modifiers.h"
#include "include/my_printf.h"
#include "include/my.h"
#include "include/memory_utils.h"
#include <stdlib.h>
#include <stdarg.h>

void free_struct(char *buf, parts_t parts)
{
    free(buf);
    free(parts.flags);
    free(parts.lmod);
}

const command_t *get_command(char *buf)
{
    for (int index = 0; func_map[index].fptr != NULL; index += 1)
        if (buf[my_strlen(buf) - 1] == func_map[index].command)
            return &func_map[index];
    return 0;
}

void search_for_combined(char *remain, int *i, va_list list, int *counter)
{
    int j = 0;

    for (j = 0; remain[j] != '%' && remain[j] != '\0'; j++) {
        *i += 1;
        my_putchar(remain[j]);
        *counter += 1;
    }
    if (remain[j] == '\0')
        return;
    search(list, &remain[j], i, counter);
}
