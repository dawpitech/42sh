/*
** EPITECH PROJECT, 2023
** my_strcpy
** File description:
** Copy a string into another
*/

#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int len = my_strlen(src);

    for (int i = 0; src[i] != '\0'; i += 1) {
        dest[i] = src[i];
    }
    dest[len] = '\0';
    return dest;
}
