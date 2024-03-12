/*
** EPITECH PROJECT, 2023
** list of modifiers
** File description:
** title
*/

#pragma once
#include <stdarg.h>
#include <stddef.h>

typedef struct parts_s {
    char *buf;
    char *flags;
    int width;
    int precision;
    int precision_val;
    char *lmod;
} parts_t;

#include "extra_modifiers.h"

int percent_c(va_list list, parts_t parts);
int percent_percent(va_list list, parts_t parts);
int percent_s(va_list list, parts_t parts);
int percent_d(va_list list, parts_t parts);
int percent_f(va_list list, parts_t parts);

typedef struct command_s {
    char command;
    int (*fptr)(va_list list, parts_t);
} command_t;

static const command_t func_map[] = {
    {.command = 'c', .fptr = percent_c},
    {.command = '%', .fptr = percent_percent},
    {.command = 's', .fptr = percent_s},
    {.command = 'd', .fptr = percent_d},
    {.command = 'i', .fptr = percent_d},
    {.command = 'o', .fptr = percent_d},
    {.command = 'x', .fptr = percent_d},
    {.command = 'b', .fptr = percent_d},
    {.command = 'f', .fptr = percent_f},
    {.command = 'F', .fptr = percent_f},
    {.command = 'g', .fptr = percent_f},
    {.command = 'G', .fptr = percent_f},
    {.command = 'e', .fptr = percent_f},
    {.command = 'E', .fptr = percent_f},
    {.command = 'p', .fptr = percent_p},
    {.command = '\0', .fptr = NULL}
};
