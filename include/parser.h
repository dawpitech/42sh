/*
** EPITECH PROJECT, 2024
** include
** File description:
** parser
*/


#ifndef PARSER_H
    #define PARSER_H

    #include "lexer.h"
    #include <stddef.h>

typedef struct commands_s {
    char *str;
    char **args;
    int fd_in;
    int fd_out;
} commands_t;

typedef struct pipe_s {
    commands_t *tab_command;
    size_t size;
} pipe_t;

typedef struct or_s {
    pipe_t *tab_pipe;
    size_t size;
} or_t;

typedef struct and_s{
    or_t *tab_or;
    size_t size;
} and_t;

typedef struct semicol_s {
    pipe_t *tab_pipe;
    size_t size;
} semicol_t;

typedef struct root_s {
    semicol_t *tab_sc;
    size_t size;
} root_t;

#endif /* PARSER_H */
