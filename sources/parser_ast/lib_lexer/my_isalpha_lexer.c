/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_char_is_alpha
*/

int my_isalpha_lexer(char const c)
{
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != '_'
        && c != '.' && c != '/')
        return 1;
    return 0;
}