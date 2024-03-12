/*
** EPITECH PROJECT, 2023
** my_strbcat
** File description:
** Concatenates n byte from a string into another.
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int l_dest = my_strlen(dest);
    int i;

    for (i = l_dest; i < (l_dest + nb); i += 1) {
        dest[i] = src[i - l_dest];
    }
    return dest;
}
