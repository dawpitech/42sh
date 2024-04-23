/*
** EPITECH PROJECT, 2024
** include
** File description:
** parser
*/

#ifndef PARSER_H
    #define PARSER_H

    #include "lexer_ast.h"
    #include <stddef.h>

typedef struct commands_s {
    char *str;
    char **args;
    int fd_in;
    int fd_out;
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

// MEMORY MANAGEMENT
char **realloc_args(char **old_args, token_t *token);
int realloc_tab_cmd(pipe_t *pipe);
int realloc_tab_sc(semicol_t *sm);
int realloc_tab_pipe(pipe_t *pipe);
pipe_t *init_pipe(void);
semicol_t *init_semicol(void);
root_t *init_root(void);
void free_parser(root_t *root);
void free_parser_lexer(root_t *root, list_t *list);
and_t *init_and(void);
or_t *init_or(void);

// PARSER FUNCTION
commands_t *parser_command(token_t **token);
pipe_t *parser_pipe(token_t **token);
semicol_t *parser_semicol(token_t **token);
and_t *parser_and(token_t **token);
or_t *parser_or(token_t **token);

// UTILS
int init_fd(pipe_t *s_pipe);
pipe_t *loop_pipe(pipe_t *new_pipe, token_t **token);
pipe_t *check_redirect_symbol(pipe_t *new_pipe, token_t **token);
pipe_t *fill_first_cmd_tab(pipe_t *new_pipe, token_t **token);
semicol_t *loop_semicol(semicol_t *new, token_t **token);
root_t *loop_root(root_t *root, token_t **token);
pipe_t *loop_redirect(pipe_t *new_pipe, token_t **token);

#endif /* PARSER_H */
