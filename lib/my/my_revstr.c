/*
** EPITECH PROJECT, 2023
** my_revstr
** File description:
** Reverse a string
*/

#include "my.h"

char *my_revstr(char *str)
{
    int len = my_strlen(str);
    char temp;

    for (int i = 0; i < (len / 2); i += 1) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    return str;
}
