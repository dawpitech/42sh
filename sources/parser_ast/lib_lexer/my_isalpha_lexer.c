/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_char_is_alpha
*/

#include "lexer_ast.h"

int my_isalpha_lexer(char const c)
{
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != '_'
        && c != '.' && c != '/' && c != '*' && c != ',')
        return 1;
    return 0;
}
