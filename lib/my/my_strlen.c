/*
** EPITECH PROJECT, 2023
** my_strlen
** File description:
** Return the number of character in a str passed as a parameter
*/

int my_strlen(char const *str)
{
    int len = 0;

    if (!str)
        return 1;
    for (int i = 0; str[i] != '\0'; i += 1) {
        len += 1;
    }
    return (len);
}
