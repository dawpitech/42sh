/*
** EPITECH PROJECT, 2024
** B-CPE-110-BDX-1-1-secured-maxime.goyheneche
** File description:
** str_utils header
*/

#include <malloc.h>
#include <stddef.h>
#include <unistd.h>

#include "str_utils.h"

int my_strlen_private(char const *str)
{
    int rst = 0;

    if (str == NULL)
        return -1;
    for (; str[rst] != '\0'; rst += 1);
    return rst;
}

long my_printstr_private(char const *str)
{
    return write(1, str, my_strlen_private(str));
}

char *my_strdup_private(char const *str)
{
    char *new_str;
    int str_len;

    if (str == NULL)
        return NULL;
    str_len = my_strlen_private(str);
    if (str_len <= 0)
        return NULL;
    new_str = malloc(sizeof(char) * (str_len + 1));
    if (new_str == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i += 1) {
        new_str[i] = str[i];
    }
    new_str[my_strlen_private(str)] = '\0';
    return new_str;
}
