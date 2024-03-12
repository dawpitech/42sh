/*
** EPITECH PROJECT, 2023
** my_strcat
** File description:
** Concatenates two string.
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int l_dest = my_strlen(dest);
    int l_src = my_strlen(src);
    int i;

    for (i = l_dest; i <= (l_dest + l_src); i += 1) {
        dest[i] = src[i - l_dest];
    }
    return dest;
}
