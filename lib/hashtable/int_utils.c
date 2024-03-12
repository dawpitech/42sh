/*
** EPITECH PROJECT, 2024
** B-CPE-110-BDX-1-1-secured-maxime.goyheneche
** File description:
** int_utils header
*/

#include <malloc.h>

#include "../include/int_utils.h"

int my_int_len(unsigned int i)
{
    if (i <= 9)
        return 1;
    return (my_int_len(i / 10) + 1);
}

char *my_int_to_str(unsigned int value)
{
    int value_len = my_int_len(value);
    char *value_str = malloc(sizeof(char) * (value_len + 1));

    value_str[value_len] = '\0';
    do {
        value_len -= 1;
        value_str[value_len] = (char) ((value % 10) + '0');
        value /= 10;
    } while (value != 0);
    return value_str;
}
