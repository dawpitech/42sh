/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_list_len
*/

#include "lexer.h"

int my_list_len(list_t *list)
{
    int count = 0;

    if (!list)
        return -1;
    for (token_t *tmp = list->head; tmp != NULL; tmp = tmp->next) {
        count += 1;
    }
    return count;
}
