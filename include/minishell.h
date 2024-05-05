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

    #define RET_ERROR 84
    #define RET_VALID 0
    #define EXIT_FAILURE_TECH 84
    #define EXIT_SUCCESS_TECH 0
    #define NO_CMD_FOUND (-42)
    #include <stdlib.h>
    #include <stdbool.h>
    #include "lexer_ast.h"
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

typedef struct root_s root_t;
typedef struct shell_s shell_t;

typedef struct commands_s {
    char *exec_name;
    char **argv;
    int argc;
    int fd_in;
    int fd_out;
    bool job_control;
    shell_t *shell;
    root_t *sub_shell;
} commands_t;

typedef struct pipe_s {
    commands_t **tab_command;
    size_t size;
} pipe_t;

typedef struct or_s {
    pipe_t **tab_pipe;
    size_t size;
} or_t;

typedef struct and_s {
    or_t **tab_or;
    size_t size;
} and_t;

typedef struct semicol_s {
    and_t **tab_and;
    size_t size;
} semicol_t;

typedef struct root_s {
    semicol_t **tab_sc;
    size_t size;
} root_t;

typedef struct env_var_s {
    char *key;
    char *value;
    struct env_var_s *next;
} env_var_t;

typedef struct {
    char *raw_input;
} prompt_t;

typedef struct {
    char *line;
    time_t timestamp;
} history_entry_t;

typedef struct shell_s {
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

// MEMORY MANAGEMENT
int realloc_args(commands_t *command, token_t *token);
int realloc_tab_cmd(pipe_t *pipe);
int realloc_tab_sc(root_t *root);
int realloc_tab_pipe(or_t *or_obj);
int realloc_tab_and(semicol_t *sm);
pipe_t *init_pipe(void);
semicol_t *init_semicol(void);
root_t *init_root(void);
void free_parser(root_t *root);
void free_parser_lexer(root_t *root, list_t *list);
and_t *init_and(void);
or_t *init_or(void);

// PARSER FUNCTION
commands_t *parser_command(token_t **token, shell_t *shell);
pipe_t *parser_pipe(token_t **token, shell_t *shell);
semicol_t *parser_semicol(token_t **token, shell_t *shell);
and_t *parser_and(token_t **token, shell_t *shell);
or_t *parser_or(token_t **token, shell_t *shell);

// UTILS
int init_fd(pipe_t *s_pipe);
void fill_arguments(token_t **token, commands_t *c);
pipe_t *loop_pipe(pipe_t *new_pipe, token_t **token, shell_t *shell);
pipe_t *check_redirect_symbol(pipe_t *new_pipe, token_t **token);
pipe_t *fill_first_cmd_tab(pipe_t *new_pipe, token_t **token);
semicol_t *loop_semicol(semicol_t *new, token_t **token, shell_t *shell);
root_t *loop_root(root_t *root, token_t **token, shell_t *shell);
pipe_t *loop_redirect(pipe_t *new_pipe, token_t **token);
or_t *loop_or(or_t *or_obj, token_t **token, shell_t *shell);
and_t *loop_and(and_t *and_obj, token_t **token, shell_t *shell);

// PARENTHESE
int handle_parenthese(pipe_t *pipe, token_t **node, shell_t *shell);

// NODES COMPUTES
int compute_root(root_t *root);
int compute_semicolon(semicol_t *semicol);
int compute_and(and_t *and_obj);
int compute_or(or_t *or_obj);
int compute_pipe(pipe_t *pipe_obj);
int compute_cmd(commands_t *cmd);

int minishell(__attribute__((unused)) int argc,
    __attribute__((unused)) char **argv, char **env);
int present_prompt(shell_t *shell);
root_t *parse_input(char *raw_input, shell_t *shell);
int run_command(shell_t *shell, commands_t *command);
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
