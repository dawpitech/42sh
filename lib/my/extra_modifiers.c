/*
** EPITECH PROJECT, 2023
** extra_modifiers
** File description:
** title
*/

#include "include/modifiers.h"
#include "include/extra_modifiers.h"
#include "include/my.h"
#include <stdlib.h>

int percent_p(va_list list, parts_t __attribute__((unused)) parts)
{
    int longs = 0;
    unsigned long nbr = 0;
    char *base = malloc(17);

    my_strcpy(base, "0123456789abcdef");
    nbr = va_arg(list, unsigned long);
    my_putstr("0x");
    longs = my_putnbr_base((long)nbr, &base);
    return longs + 2;
}
