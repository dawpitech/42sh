/*
** EPITECH PROJECT, 2023
** my_printf
** File description:
** my_printf (uwu)
*/

#include <stdio.h>
#include <stdlib.h>
#include "include/my.h"
#include "include/modifiers.h"
#include "include/my_printf.h"
#include "include/memory_utils.h"

static parts_t get_lmod(parts_t *parts)
{
    int j = 0;

    for (j = 0; !IS_ALPHA(parts->buf[j]); j++);
    my_strcat(parts->lmod, &parts->buf[j]);
    parts->lmod[my_strlen(parts->lmod) - 1] = '\0';
    return *parts;
}

static int is_good_not_alpha_num(char c)
{
    char buf[] = {'%', '.', '*', '#', '-', '+', '\0'};

    for (int i = 0; buf[i] != '\0'; i++)
        if (c == buf[i])
            return 1;
    return 0;
}

static parts_t prepare_struct(void)
{
    parts_t parts;

    parts.lmod = malloc(6);
    my_memset(parts.lmod, 0, 6);
    parts.flags = malloc(6);
    my_memset(parts.flags, 0, 6);
    parts.width = 0;
    parts.precision = 0;
    parts.precision_val = 0;
    return parts;
}

parts_t create_struct(char *buf)
{
    parts_t parts = prepare_struct();
    int got_width = 0;
    int i = 0;

    parts.buf = buf;
    for (i = 1; buf[i] != '\0'; i++) {
        if (!IS_ALPHANUM(buf[i]))
            my_strncat(parts.flags, &buf[i], 1);
        if (buf[i] == '.') {
            parts.precision = 1;
            got_width = 1;
        }
        if (IS_NUM(buf[i]) && got_width && !parts.precision_val)
            parts.precision_val = my_getnbr(&buf[i]);
        if (IS_NUM(buf[i]) && !got_width) {
            parts.width = my_getnbr(&buf[i]);
            got_width = 1;
        }
    }
    return get_lmod(&parts);
}

static char *my_strappendn(char *buf, int i, int *alrd_checked)
{
    char *str = malloc(my_strlen(buf) + 1);
    int k = 0;

    my_memset(str, 0, my_strlen(buf) + 1);
    *alrd_checked += 1;
    for (int j = 0; j < my_strlen(buf) + 1; j++) {
        if (j == i) {
            str[j] = '\0';
            continue;
        }
        str[j] = buf[k];
        ++k;
    }
    free(buf);
    return str;
}

void check_for_flags(int *alrd_checked, int i, char c, char **buf)
{
    char c_list[] = {'d', 'c', 'i', 'p', 's', 'f', '\0'};

    if (*alrd_checked >= 1)
        return;
    for (int j = 0; c_list[j] != '\0'; j++) {
        if (c == c_list[j]) {
            *buf = my_strappendn(*buf, i, alrd_checked);
        }
    }
}

static char *get_flag(char **buf)
{
    char c = '\0';
    int i = 0;
    int p = 0;
    char *end = 0;
    int alrd_checked = 0;

    if (!(*buf))
        return 0;
    for (i = 0; (*buf)[i] != '\0'; i++) {
        if ((((*buf)[i] == 'd' && c == 'o') || ((*buf)[i] == '%' && p == 2))
            && !alrd_checked)
            *buf = my_strappendn(*buf, i, &alrd_checked);
        if (c == '%')
            ++p;
        check_for_flags(&alrd_checked, i, c, buf);
        c = (*buf)[i];
    }
    end = &((*buf)[my_strlen(*buf) + 1]);
    return end;
}

void search(va_list list, const char *c, int *i, int *counter)
{
    char *buf = malloc(BUFFER_SIZE);
    int j = 0;
    const command_t *com = NULL;
    parts_t parts;
    char *remain = 0;

    my_memset(buf, 0, BUFFER_SIZE);
    for (j = 0; j < BUFFER_SIZE && (IS_ALPHANUM(c[j]) ||
        is_good_not_alpha_num(c[j])) && c[j] != '\0'; j++)
        buf[j] = c[j];
    buf[j] = '\0';
    remain = get_flag(&buf);
    *i += (j - my_strlen(remain));
    parts = create_struct(buf);
    com = get_command(buf);
    if (com != NULL)
        *counter += com->fptr(list, parts);
    if (remain && my_strlen(remain) > 0)
        search_for_combined(remain, i, list, counter);
    free_struct(buf, parts);
}

int my_printf(const char *format, ...)
{
    va_list list;
    int counter = 0;

    va_start(list, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%')
            search(list, &format[i], &i, &counter);
        if (format[i] == '\0')
            break;
        if (format[i] != '%') {
            my_putchar(format[i]);
            ++counter;
        }
    }
    return counter;
}
