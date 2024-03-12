/*
** EPITECH PROJECT, 2023
** my_putstr
** File description:
** Display the characters of a string passed as parameter
*/

#include "my.h"

int my_putstr(char const *str)
{
    int count = 0;

    if (!str)
        return my_putstr("(null)");
    for (int i = 0; str[i] != '\0'; i += 1) {
        my_putchar(str[i]);
        count += 1;
    }
    return (count);
}
