/*
** EPITECH PROJECT, 2024
** bonus_mysh
** File description:
** alias
*/

#include "my.h"
#include "alias.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static
int my_lenalias(alias_t **tab)
{
    int count = 0;

    if (!tab)
        return 0;
    for (; tab[count] != NULL; count ++);
    return count;
}

static
char *loop_contact_command(char **tab)
{
    char *new_str = NULL;

    if (!tab)
        return NULL;
    new_str = my_strdup(tab[2]);
    if (tab[3] != NULL)
        for (size_t i = 3; tab[i] != NULL; i ++) {
            new_str = my_strcat(new_str, " ");
            new_str = my_strcat(new_str, tab[i]);
            if (tab[i + 1] != NULL)
                new_str = my_strcat(new_str, " ");
        }
    return new_str;
}

static
int add_in_tab_alias(char **tab, shell_t *mysh)
{
    alias_t **new_alias = NULL;
    char *link_command = NULL;
    int len = 0;

    if (!tab || !mysh)
        return FAILURE;
    if (my_tablen(tab) == 2)
        return SUCCESS;
    len = my_lenalias(mysh->alias);
    new_alias = malloc(sizeof(alias_t *) * (len + 2));
    if (mysh->alias != NULL)
        for (int i = 0; mysh->alias[i] != NULL; i ++) {
            new_alias[i] = mysh->alias[i];
        }
    new_alias[len] = malloc(sizeof(alias_t));
    new_alias[len]->alias = my_strdup(tab[1]);
    link_command = loop_contact_command(tab);
    new_alias[len]->link_command = link_command;
    new_alias[len + 1] = NULL;
    free(mysh->alias);
    mysh->alias = NULL;
    mysh->alias = new_alias;
    return SUCCESS;
}

int exec_alias(mysh_t *mysh)
{
    char **tab = NULL;
    char *separator[3] = {"\n", " ", NULL};

    if (!mysh || !mysh->input) {
        return FAILURE;
    }
    tab = my_str_to_word_array(mysh->input, separator);
    if (my_tablen(tab) == 1) {
        display_alias(mysh->alias);
        return SUCCESS;
    }
    if (add_in_tab_alias(tab, mysh) == FAILURE)
        return FAILURE;
    return SUCCESS;
}
