/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** Display the number given as a parameter
*/

#include "my.h"

static
void my_print_nbr(long nb)
{
    if (nb == 0) {
        return;
    } else {
        my_print_nbr(nb / 10);
    }
    my_putchar('0' + -(nb % 10));
}

static
int count_len_nbr(long nb)
{
    double len = nb < 0;

    while (nb) {
        nb /= 10;
        len += 1;
    }
    return (len);
}

int my_put_nbr(long nb)
{
    if (nb < 0) {
        my_putchar('-');
        my_print_nbr(nb);
    } else if (nb == 0) {
        my_putchar('0');
    } else {
        my_print_nbr(-nb);
    }
    return (count_len_nbr(nb));
}
