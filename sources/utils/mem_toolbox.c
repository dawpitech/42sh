/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** mem_toolbox header
*/

#include <malloc.h>
#include <stddef.h>

#include "mem_toolbox.h"

void my_memcpy(void *dest, void *src, size_t size)
{
    char *cdest = (char *) dest;
    char *csrc = (char *) src;

    for (size_t i = 0; i < size; i += 1)
        cdest[i] = csrc[i];
}

void *my_realloc(void *ptr, size_t new_size, size_t old_size)
{
    void *new_ptr;

    if (ptr == NULL)
        return malloc(new_size);
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;
    my_memcpy(new_ptr, ptr, old_size);
    free(ptr);
    return new_ptr;
}
