/*
** EPITECH PROJECT, 2024
** B-CPE-110-BDX-1-1-secured-maxime.goyheneche
** File description:
** hashtable_content_manager header
*/

#include <stddef.h>
#include <stdlib.h>

#include "../include/hashtable_content_manager.h"
#include "../include/str_utils.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"

static
int insert_node_in_cell(cell_content_t **cell, char *value, int hashed_key)
{
    cell_content_t *new = malloc(sizeof(cell_content_t));

    if (new == NULL)
        return EXIT_FAILURE_TECH;
    new->content = my_strdup_private(value);
    new->hashed_key = (unsigned) hashed_key;
    new->next = *cell;
    *cell = new;
    return EXIT_SUCCESS;
}

static
int rm_node_from_cell(cell_content_t **cell, unsigned int hashed_key)
{
    cell_content_t *current_rc = *cell;
    cell_content_t *prev = NULL;

    while (current_rc != NULL) {
        if (current_rc->hashed_key == hashed_key && prev != NULL) {
            prev->next = current_rc->next;
            free(current_rc->content);
            free(current_rc);
            return EXIT_SUCCESS;
        }
        if (current_rc->hashed_key == hashed_key && prev == NULL) {
            *cell = current_rc->next;
            free(current_rc->content);
            free(current_rc);
            return EXIT_SUCCESS;
        }
        prev = current_rc;
        current_rc = current_rc->next;
    }
    return EXIT_FAILURE_TECH;
}

static
char *find_node_content(cell_content_t *cell, unsigned int hashed_key)
{
    cell_content_t *curr = cell;

    while (curr != NULL) {
        if (curr->hashed_key == hashed_key) {
            return curr->content;
        }
        curr = curr->next;
    }
    return NULL;
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int hashed_key;

    if (ht == NULL || key == NULL || value == NULL)
        return EXIT_FAILURE_TECH;
    hashed_key = ht->hash_function(key, ht->size);
    if (hashed_key == 0)
        return EXIT_FAILURE_TECH;
    if (ht_search(ht, key) != NULL)
        ht_delete(ht, key);
    return insert_node_in_cell(&(ht->cells[hashed_key % ht->size]),
        value, hashed_key);
}

int ht_delete(hashtable_t *ht, char *key)
{
    int hashed_key;

    if (ht == NULL || key == NULL)
        return EXIT_FAILURE_TECH;
    hashed_key = ht->hash_function(key, my_strlen_private(key));
    return rm_node_from_cell(&(ht->cells[hashed_key % ht->size]),
        (unsigned) hashed_key);
}

char *ht_search(hashtable_t *ht, char *key)
{
    int hashed_key;

    if (ht == NULL || key == NULL)
        return NULL;
    hashed_key = ht->hash_function(key, my_strlen_private(key));
    return find_node_content(ht->cells[hashed_key % ht->size],
        (unsigned) hashed_key);
}

#pragma clang diagnostic pop
