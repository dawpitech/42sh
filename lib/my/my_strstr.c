/*
** EPITECH PROJECT, 2023
** my_strstr
** File description:
** Reproduce the behavior of strstr function, find a substring in a string
*/

#include <stddef.h>
#include "my.h"

char *my_strstr(char *str, char const *to_find)
{
    int len_str = my_strlen(str);
    int len_str_to_find = my_strlen(to_find);

    if (my_strlen(to_find) == 0) {
        return (str);
    }
    for (int i = 0; i < len_str - len_str_to_find + 1; i += 1) {
        if (my_strncmp(&str[i], to_find, my_strlen(to_find)) == 0) {
            return (&str[i]);
        }
    }
    return (NULL);
}
