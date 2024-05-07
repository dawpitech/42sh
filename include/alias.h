/*
** EPITECH PROJECT, 2024
** include
** File description:
** alias
*/

#ifndef ALIAS_H
    #define ALIAS_H

    #include "minishell.h"

typedef struct alias_s {
    char *alias;
    char *cmd;
} alias_t;

int handle_realoc(shell_t *shell, char **argv);
void print_alias(alias_t **aliases);
int count_aliases(alias_t **aliases);
int handle_null(shell_t *shell, char **argv);
int rename_command(shell_t *shell, int argv);
void compare_alias(alias_t **alias, commands_t *cmd);
int rename_command(shell_t *shell, int argv);
int alias_handler(shell_t *shell, int argc, char **argv);


#endif /* ALIAS_H */
