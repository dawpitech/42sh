/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** Return a pointer to a copy of the string passed
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char const *src)
{
    char *dup;
    int src_len;

    if (src == NULL)
        return NULL;
    src_len = my_strlen(src);
    dup = malloc(sizeof(char) * (src_len + 1));
    my_strcpy(dup, src);
    return (dup);
}
