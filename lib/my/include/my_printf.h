/*
** EPITECH PROJECT, 2023
** my_printf.h
** File description:
** title
*/

#pragma once
#include <stdarg.h>
#include "modifiers.h"
#define BUFFER_SIZE 256

void search(va_list list, const char *c, int *i, int *counter);
parts_t create_struct(char *buf);
int my_printf(const char *format, ...);
