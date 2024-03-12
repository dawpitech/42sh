/*
** EPITECH PROJECT, 2023
** my_strcapitalize
** File description:
** Capitalize the first letter of each word
*/

#include "my.h"

static
int is_num(char str)
{
    return (str >= '0' && str <= '9');
}

static
int is_low(char str)
{
    return (str >= 'a' && str <= 'z');
}

static
int is_up(char str)
{
    return (str >= 'A' && str <= 'Z');
}

static
int is_alpha(char str)
{
    return (is_low(str) || is_up(str));
}

char *my_strcapitalize(char *str)
{
    int is_start = 1;

    for (int i = 0; str[i] != '\0'; i += 1) {
        if (!is_alpha(str[i]) && !is_num(str[i])) {
            is_start = 1;
            continue;
        }
        if (is_low(str[i]) && is_start) {
            str[i] = str[i] - 32;
        }
        if (is_up(str[i]) && !is_start) {
            str[i] = str[i] + 32;
        }
        is_start = 0;
    }
    return str;
}
