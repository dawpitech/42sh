/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** path_explorer header
*/

#include <dirent.h>
#include <string.h>

#include "path_explorer.h"
#include "my.h"
#include "my_printf.h"

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
        if (my_strcmp(dirent->d_name, bin_searched) == 0) {
            closedir(dir);
            return RET_VALID;
        }
        dirent = readdir(dir);
    }
    closedir(dir);
    return RET_ERROR;
}

char *search_bin(shell_t *shell, sh_command_t *cmd)
{
    char *path = my_strdup(get_env_var(shell, "PATH")->value);
    char *result = strtok(path, ":");
    char *rt;

    while (result != NULL) {
        if (find_bin_in_dir(cmd->argv[0], result) == RET_VALID) {
            rt = my_strdup(result);
            free(path);
            return rt;
        }
        result = strtok(NULL, ":");
    }
    free(path);
    return NULL;
}
