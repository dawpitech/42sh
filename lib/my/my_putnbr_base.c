/*
** EPITECH PROJECT, 2023
** my_putnbr_base
** File description:
** Display a decimal number into a given base
*/

#include "my.h"
#include <stdlib.h>

int nbr_len(long long nb)
{
    double len = nb <= 0;

    while (nb) {
        nb /= 10;
        ++len;
    }
    return len;
}

static
void my_print_nbr_base(long long nb, char const *base)
{
    if (nb == 0) {
        return;
    } else {
        my_print_nbr_base(nb / my_strlen(base), base);
    }
    my_putchar(base[-(nb % my_strlen(base))]);
}

int my_putnbr_base(long long nb, char **base)
{
    if (nb < 0) {
        my_putchar('-');
        my_print_nbr_base(nb, *base);
    } else if (nb == 0) {
        my_putchar('0');
    } else {
        my_print_nbr_base(-nb, *base);
    }
    free(*base);
    return nbr_len(nb);
}
