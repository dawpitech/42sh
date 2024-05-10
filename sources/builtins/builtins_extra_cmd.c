/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** builtins_extra_cmd header
*/

#include <stdio.h>

#include "minishell.h"
#include "builtins_cmd.h"
#include "path_explorer.h"
#include "utils.h"

int execute_which(shell_t *shell, int argc, char **argv)
{
    char *path;
    bool all_success = true;

    if (argc < 2)
        return EXIT_FAILURE_TECH;
    for (int i = 1; i < argc; i += 1) {
        path = search_bin(shell, argv[i]);
        if (path == NULL) {
            my_put_stderr(argv[i]);
            my_put_stderr(" not found.\n");
            all_success = false;
            continue;
        }
        printf("%s/%s\n", path, argv[i]);
    }
    return all_success ? EXIT_SUCCESS_TECH : EXIT_FAILURE_TECH;
}
