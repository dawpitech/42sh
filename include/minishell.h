/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** minishell header
*/

#ifndef MINISHELL_MINISHELL_H
    #define MINISHELL_MINISHELL_H

    #include <stdbool.h>
    #include <stdlib.h>

    #include "lexer_ast.h"
    #include "parser_ast.h"

    #define RET_ERROR 84
    #define RET_VALID 0
    #define EXIT_FAILURE_TECH 84
    #define EXIT_SUCCESS_TECH 0
    #define NO_CMD_FOUND (-42)
    #define CMD_IS_A_PIPE (-69)
    #define HISTORY_FILE (".history")

    #define IS_LOW(c) (((c) >= 'a' && (c) <= 'z') ? (1) : (0))
    #define IS_UP(c) (((c) >= 'A' && (c) <= 'Z') ? (1) : (0))
    #define IS_ALPHA(c) ((IS_LOW(c) || IS_UP(c)) ? (1) : (0))
    #define IS_NUM(c) (((c) >= '0' && (c) <= '9') ? (1) : (0))
    #define IS_ALPHANUM(c) ((IS_ALPHA(c) || IS_NUM(c)) ? (1) : (0))
    #define ABS(c) (((c) > 0) ? (c) : (- (c)))
    #define POS(c) (((c) > 0) ? (c) : (0))

    #ifndef WCOREDUMP
        #define WCOREDUMP(x) 0
    #endif
int minishell(__attribute__((unused)) int argc,
    __attribute__((unused)) char **argv, char **env);
typedef struct env_var_s {
    char *key;
    char *value;
    struct env_var_s *next;
} env_var_t;
typedef enum {
    EXPR,
    REDR,
    REDL,
    DBL_REDR,
    DBL_REDL,
    // PIPE,
    // OR,
    // AND
} cmd_t;
typedef struct {
    char **argv;
    int argc;
    cmd_t type;
    char *stdin_file;
    char *stdout_file;
    int fd_stdin;
    int fd_stdout;
} sh_command_t;
typedef struct {
    sh_command_t *commands;
    int nb_commands;
    char *raw_input;
} prompt_t;
typedef struct {
    char *line;
    time_t timestamp;
} history_entry_t;
typedef struct {
    prompt_t *prompt;
    env_var_t *env_vars;
    list_t *list;
    root_t *root;
    history_entry_t **history_entries;
    unsigned int history_size;
    int nb_env_var;
    bool running;
    bool cmds_valid;
    bool isatty;
    char *current_path;
    char *last_path;
    int last_exit_code;
} shell_t;
int present_prompt(shell_t *shell);
root_t *parse_input(char *raw_input);
int run_command(shell_t *shell, sh_command_t *cmd);
char **get_env_array(shell_t *shell);
void free_env_array(char **array);
env_var_t *get_env_var(shell_t *context, char *key);
int add_env_var(shell_t *context, char *key, char *value);
int parse_env_var(shell_t *context, char **env);
void free_env_vars(shell_t *context);
int remove_env_var(shell_t *context, char *key);
void handle_ctrl_c(int signal);
void history_add(shell_t *shell, char const *line);
history_entry_t *history_get(shell_t *shell, int index);
int write_hist(shell_t *shell);
int load_history(shell_t *shell);
void history_free(shell_t *shell);
list_t *lexer(char *raw_input, list_t *list);
int parser_of_lexer(shell_t *mysh);
#endif //MINISHELL_MINISHELL_H
