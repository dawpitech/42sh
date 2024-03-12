/*
** EPITECH PROJECT, 2023
** implementations of modifiers
** File description:
** title
*/

#include "include/my.h"
#include "include/modifiers.h"
#include <stdio.h>
#include <stdlib.h>

int percent_c(va_list list, parts_t __attribute__((unused)) parts)
{
    char c = '\0';
    int spaces = 0;

    if (parts.flags[0] == '*')
        spaces = va_arg(list, int);
    c = va_arg(list, int);
    for (int i = 0; i < (spaces - 1); i++)
        my_putchar(' ');
    my_putchar(c);
    return 1 + POS(spaces - 1);
}

int percent_percent(va_list __attribute__((unused)) list,
    parts_t __attribute__((unused)) parts)
{
    my_putchar('%');
    return 1;
}

int percent_s(va_list list, parts_t parts)
{
    char *str = 0;
    int spaces = 0;
    int len = 0;

    if (parts.flags[0] == '*')
        spaces = va_arg(list, int);
    str = va_arg(list, char *);
    for (int i = 0; i < (spaces - my_strlen(str)); i++)
        my_putchar(' ');
    len = my_putstr(str);
    return len + POS(spaces - my_strlen(str));
}

static int print_spaces(parts_t parts, int size, va_list list)
{
    static int spaces = 0;
    int i = 0;

    if (parts.flags[0] == '*' && !spaces) {
        spaces = va_arg(list, int);
        return 0;
    }
    for (i = 0; i < (spaces - size); i++)
        my_putchar(' ');
    spaces = 0;
    return i;
}

int percent_f(va_list list, parts_t parts)
{
    float value = 0;
    int precision = 6;
    int spaces = 0;

    if (parts.precision) {
        precision = parts.precision_val;
    }
    print_spaces(parts, 0, list);
    value = (float) va_arg(list, double);
    spaces = print_spaces(parts, nbr_len((int)value) + precision + 1, list);
    return (my_putfloat((double) value, precision) + spaces);
}

static void get_base(char *base, char c, parts_t *parts)
{
    if (c == 'i' || c == 'u' || c == 'd') {
        my_strcpy(base, "0123456789");
        return;
    }
    switch (c) {
    case 'X' :
        my_strcpy(base, "0123456789ABCDEF");
        return;
    case 'x' :
        my_strcpy(base, "0123456789abcdef");
        return;
    case 'o' :
        my_strcpy(base, "01234567");
        return;
    case 'b' :
        my_strcpy(base, "01");
        return;
    default:
        get_base(base, parts->buf[my_strlen(parts->buf) - 1], parts);
    }
}

static long get_nbr(int longs, int uint, int h, va_list list)
{
    long nbr = 0;

    if (longs && !uint && !h)
        nbr = va_arg(list, long);
    if (!longs && !uint && !h)
        nbr = va_arg(list, int);
    if (uint && !longs && !h)
        nbr = va_arg(list, unsigned int);
    if (uint && longs && !h)
        nbr = va_arg(list, unsigned long);
    if (uint && (h == 1))
        nbr = (unsigned short)va_arg(list, int);
    if (!uint && (h == 1))
        nbr = (short)va_arg(list, int);
    if (uint && h > 1)
        nbr = (unsigned char)va_arg(list, int);
    if (!uint && h > 1)
        nbr = (char)va_arg(list, int);
    return nbr;
}

int percent_d(va_list list, parts_t parts)
{
    long nbr = 0;
    int longs = 0;
    int uint = 0;
    int h = 0;
    char *base = malloc(256);

    print_spaces(parts, 0, list);
    for (int i = 0; parts.lmod[i] != '\0'; i++) {
        if (parts.lmod[i] == 'z')
            parts.lmod[i] = 'q';
        h += parts.lmod[i] == 'h';
        longs += (parts.lmod[i] == 'l' || parts.lmod[i] == 'q');
        uint = parts.lmod[i] == 'u';
        get_base(base, parts.lmod[i], &parts);
    }
    if (my_strlen(parts.lmod) == 0)
        get_base(base, '\0', &parts);
    nbr = get_nbr(longs, uint, h, list);
    longs = print_spaces(parts, nbr_len(nbr), list);
    return my_putnbr_base((long)nbr, &base) + longs;
}
