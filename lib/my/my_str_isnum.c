/*
** EPITECH PROJECT, 2023
** my_str_isnum
** File description:
** Return 1 if the string passed only contains digits, return 0 if not
*/

#include "my.h"

int my_str_isnum(char const *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (!(IS_NUM(str[i]))) {
            return (0);
        }
    }
    return (1);
}
