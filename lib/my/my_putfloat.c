/*
** EPITECH PROJECT, 2023
** my_putfloat
** File description:
** putfloat
*/

#include "my.h"

static
int resolve_zero_issues(long temp, int precision)
{
    int diff = (precision - nbr_len(temp));
    int p_chars = 0;

    if (temp == 0)
        diff += 1;
    for (int i = 0; i < diff; i += 1) {
        my_putchar('0');
        p_chars += 1;
    }
    return (p_chars);
}

static
long resolve_rounding(long temp, double f_p)
{
    long decimal = (long) (f_p * 10);

    if (decimal >= 5)
        temp += 1;
    return (temp);
}

int my_putfloat(double nb, int precision)
{
    long decimal = (long) nb;
    double floating_p = 0;
    long temp = 0;
    int printed_char = 0;

    floating_p = nb - decimal;
    printed_char += my_put_nbr(decimal);
    my_putchar('.');
    printed_char += 1;
    for (int i = 0; i < precision; i += 1) {
        floating_p = (floating_p * 10);
        decimal = (long) floating_p;
        temp = (temp * 10) + decimal;
        floating_p = floating_p - decimal;
    }
    temp = resolve_rounding(temp, floating_p);
    printed_char += resolve_zero_issues(temp, precision);
    if (temp != 0)
        printed_char += my_put_nbr(temp);
    return (printed_char);
}
