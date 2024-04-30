/*
** EPITECH PROJECT, 2024
** include
** File description:
** alias
*/

#ifndef ALIAS_H
    #define ALIAS_H

    #include "../include/minishell.h"

typedef struct alias_s {
    char *alias;
    char *link_command;
} alias_t;

void display_alias(alias_t **alias_tab);
int exec_alias(shell_t *mysh);

#endif /* ALIAS_H */
