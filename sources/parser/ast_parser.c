/*
** EPITECH PROJECT, 2024
** parser
** File description:
** ast_parser
*/

#include <stdio.h>
#include <string.h>

#include "minishell.h"
#include "my.h"
#include "lexer.h"
#include "utils.h"
#include "pipe_handler.h"
#include "parser.h"

static
root_t *init_root(void)
{
    root_t *root = malloc(sizeof(root_t));

    if (!root)
        return NULL;
    root->size = 0;
    root->tab_sc = NULL;
    return root;
}

root_t *loop_root(root_t *root, token)

int parse_input(shell_t *shell)
{
    char *const input = shell->prompt->raw_input;
    lexer_t lexer = lexer_new(input, strlen(input));
    token_t token = lexer_next(&lexer);
    root_t *root = init_root(); 

    if (!root || token.kind != TOKEN_SYMBOL || token.kind != TOKEN_AND ||
        token.kind != TOKEN_END) {
        dprintf(stderr, "Invalid null command.");
        return RET_ERROR;
    }
    return RET_VALID;
}
