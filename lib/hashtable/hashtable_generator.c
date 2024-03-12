/*
** EPITECH PROJECT, 2024
** B-CPE-110-BDX-1-1-secured-maxime.goyheneche
** File description:
** hashtable_generator header
*/

#include <malloc.h>

#include "hastable_generator.h"

static
void initialize_cells(hashtable_t *hashtable)
{
    for (int i = 0; i < hashtable->size; i += 1)
        hashtable->cells[i] = NULL;
}

hashtable_t *new_hashtable(int (*hash_ptr)(char *, int), int len)
{
    hashtable_t *hashtable = malloc(sizeof(hashtable_t));

    if (hashtable == NULL || len <= 0 || hash_ptr == NULL) {
        if (hashtable != NULL)
            free(hashtable);
        return NULL;
    }
    hashtable->cells = malloc(sizeof(cell_content_t *) * len);
    if (hashtable->cells == NULL) {
        free(hashtable);
        return NULL;
    }
    hashtable->hash_function = hash_ptr;
    hashtable->size = len;
    initialize_cells(hashtable);
    return hashtable;
}
