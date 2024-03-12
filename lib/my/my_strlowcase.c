/*
** EPITECH PROJECT, 2023
** my_strlowcase
** File description:
** Put every letter of every word in lower case
*/

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] >= 65 && str[i] <= 90) {
            str[i] = str[i] + 32;
        }
    }
    return (str);
}
