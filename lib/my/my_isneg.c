/*
** EPITECH PROJECT, 2023
** my_isneg
** File description:
** display N if the integer passed is negative, P if it's positive
*/

#include "my.h"

int my_isneg(int n)
{
    if (n >= 0) {
        my_putchar('P');
    } else {
        my_putchar('N');
    }
    my_putchar('\n');
    return (0);
}
