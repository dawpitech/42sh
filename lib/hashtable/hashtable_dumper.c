/*
** EPITECH PROJECT, 2024
** B-CPE-110-BDX-1-1-secured-maxime.goyheneche
** File description:
** hashtable_dumper header
*/

#include <malloc.h>
#include <stddef.h>

#include "../include/hashtable_dumper.h"
#include "../include/str_utils.h"
#include "int_utils.h"

static
void print_nodes_of_cell(cell_content_t *cell)
{
    cell_content_t *current = cell;
    char *str_tmp;

    while (current != NULL) {
        str_tmp = my_int_to_str(current->hashed_key);
        my_printstr_private("> ");
        my_printstr_private(str_tmp);
        my_printstr_private(" - ");
        my_printstr_private(current->content);
        my_printstr_private("\n");
        free(str_tmp);
        current = current->next;
    }
}

void ht_dump(hashtable_t *ht)
{
    char *tmp;

    if (ht == NULL)
        return;
    for (int i = 0; i < ht->size; i += 1) {
        my_printstr_private("[");
        tmp = my_int_to_str((unsigned) i);
        my_printstr_private(tmp);
        free(tmp);
        my_printstr_private("]:\n");
        if (ht->cells[i] != NULL) {
            print_nodes_of_cell(ht->cells[i]);
        }
    }
}
