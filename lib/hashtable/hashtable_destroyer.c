/*
** EPITECH PROJECT, 2024
** B-CPE-110-BDX-1-1-secured-maxime.goyheneche
** File description:
** hashtable_destroyer header
*/

#include <malloc.h>
#include <stddef.h>

#include "../include/hashtable_destroyer.h"

void delete_hashtable(hashtable_t *ht)
{
    if (ht == NULL)
        return;
    for (int i = 0; i < ht->size; i += 1) {
        if (ht->cells[i] != NULL) {
            free(ht->cells[i]->content);
            free(ht->cells[i]);
        }
    }
    free(ht->cells);
    free(ht);
}
