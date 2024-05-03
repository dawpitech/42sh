/*
** EPITECH PROJECT, 2024
** lib_lexer
** File description:
** my_isspace
*/

int my_isspace(char c)
{
    if (c == ' ' || c == '\f' || c == '\n' || c == '\t' || c == '\v')
        return 1;
    return 0;
}
