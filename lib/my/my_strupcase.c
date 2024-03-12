/*
** EPITECH PROJECT, 2023
** my_strupcase
** File description:
** Put every letter of every word in upper case
*/

char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] = str[i] - 32;
        }
        continue;
    }
    return (str);
}
