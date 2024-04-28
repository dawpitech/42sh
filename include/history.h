/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** history header
*/

#include <stdbool.h>

#ifndef INC_42SH_HISTORY_H
    #define INC_42SH_HISTORY_H
typedef struct {
    enum {
        SAVE,
        LOAD,
        PRINT,
    } mode;
    bool hiding_ln;
    bool timestamp_as_comment;
    bool reverse_order;
    unsigned int nb_lignes_to_print;
} history_params_t;
#endif //INC_42SH_HISTORY_H
