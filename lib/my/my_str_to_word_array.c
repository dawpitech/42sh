/*
** EPITECH PROJECT, 2023
** my_str_to_word_array
** File description:
** Split a string into words
*/

#include <stddef.h>
#include <stdlib.h>
#include "my.h"

static
char *move_pointer(char *p)
{
    while (!(IS_ALPHANUM(*p))) {
        p += 1;
    }
    return p;
}

static
int len_word(char *str)
{
    int len = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        if (IS_ALPHA(str[i]) || IS_NUM(str[i])) {
            len += 1;
        } else {
            return (len);
        }
    }
    return (len);
}

static
int count_words(char *str)
{
    int count = 0;
    int len = my_strlen(str);
    int is_start = 1;

    for (int i = 0; i < len; i += 1) {
        if (IS_ALPHANUM(str[i]) & is_start) {
            count += 1;
            is_start = 0;
            continue;
        }
        if (IS_ALPHANUM(str[i])) {
                continue;
            }
        is_start = 1;
    }
    return (count);
}

char **my_str_to_word_array(char const *str)
{
    char *str_ed = my_strdup(str);
    char *str_dp = str_ed;
    int nb_words = count_words(str_ed);
    char **rst = malloc(sizeof(char *) * (nb_words + 1));
    char *temp;

    str_ed = move_pointer(str_ed);
    for (int i = 0; i < nb_words; i += 1) {
        temp = malloc(sizeof(char) * (len_word(str_ed) + 1));
        my_strncpy(temp, str_ed, len_word(str_ed));
        my_strcat(temp, "\0");
        rst[i] = temp;
        str_ed += len_word(str_ed);
        str_ed = move_pointer(str_ed);
    }
    rst[nb_words] = NULL;
    free(str_dp);
    return rst;
}
