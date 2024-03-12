/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** minishell header
*/

#ifndef MINISHELL_MINISHELL_H
    #define MINISHELL_MINISHELL_H
    #define RET_ERROR 84
    #define RET_VALID 0
    #define EXIT_FAILURE_TECH 84
    #define EXIT_SUCCESS_TECH 0
    #define SIGN_ERROR_CODE_OFFSET 128
    #include <stdbool.h>
    #include <stdlib.h>
    #ifndef WCOREDUMP
        #define WCOREDUMP 0
    #endif

    #include "hashtable.h"
int minishell(__attribute__((unused)) int argc,
    __attribute__((unused)) char **argv, char **env);
typedef struct env_var_s {
    char *key;
    char *value;
    struct env_var_s *next;
} env_var_t;
typedef struct {
    char *raw_input;
    char **argv;
    int argc;
} prompt_t;
typedef struct {
    prompt_t *prompt;
    env_var_t *env_var;
    int nb_env_var;
    bool running;
    bool isatty;
    char *current_path;
    char *last_path;
    int last_exit_code;
} shell_t;
#endif //MINISHELL_MINISHELL_H
