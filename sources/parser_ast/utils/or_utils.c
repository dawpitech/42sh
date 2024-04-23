/*
** EPITECH PROJECT, 2024
** utils
** File description:
** or_utils
*/

#include "lexer_ast.h"
#include "parser_ast.h"
#include <stdlib.h>

or_t *loop_or(or_t *or, token_t **token)
{
    while((*token) && (*token)->type == IDENTIFIER) {
        or->tab_pipe = realloc_tab_pipe(or);

    }
}
