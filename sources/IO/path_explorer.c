/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** path_explorer header
*/

#include <dirent.h>
#include <string.h>

#include "alias.h"
#include "path_explorer.h"

static
int find_bin_in_dir(char *bin_searched, char *dir_path)
{
    struct dirent *dirent;
    DIR *dir;

    dir = opendir(dir_path);
    if (dir == NULL)
        return RET_ERROR;
    dirent = readdir(dir);
    for (int i = 0; dirent != NULL; i += 1) {
        if (strcmp(dirent->d_name, bin_searched) == 0) {
            closedir(dir);
            return RET_VALID;
        }
        dirent = readdir(dir);
    }
    closedir(dir);
    return RET_ERROR;
}

void compare_alias(alias_t **alias, commands_t *cmd)
{
    int i = 0;

    if (alias == NULL)
        return;
    while (alias[i] != NULL && alias[i]->alias != NULL && cmd->argv != NULL) {
        if (strncmp(cmd->argv[0], alias[i]->alias, strlen(cmd->argv[0])) == 0){
            free(cmd->argv[0]);
            cmd->argv[0] = strdup(alias[i]->cmd);
            return;
        }
        i++;
    }
}

char *search_bin(shell_t *shell, commands_t *cmd)
{
    char *path = strdup(get_env_var(shell, "PATH")->value);
    char *result = strtok(path, ":");
    char *rt;

    compare_alias(shell->aliases, cmd);
    while (result != NULL) {
        if (find_bin_in_dir(cmd->argv[0], result) == RET_VALID) {
            rt = strdup(result);
            free(path);
            return rt;
        }
        result = strtok(NULL, ":");
    }
    free(path);
    return NULL;
}
