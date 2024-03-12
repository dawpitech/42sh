/*
** EPITECH PROJECT, 2023
** my_strcmp
** File description:
** Reproduce the behavior of strcmp in libc
*/

#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int max_len;

    if (my_strlen(s1) > my_strlen(s2)) {
        max_len = my_strlen(s1);
    } else {
        max_len = my_strlen(s2);
    }
    for (int i = 0; i < max_len; i += 1) {
        if (s1[i] == s2[i]) {
            continue;
        }
        return (s1[i] - s2[i]);
    }
    return (0);
}
