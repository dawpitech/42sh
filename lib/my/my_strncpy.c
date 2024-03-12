/*
** EPITECH PROJECT, 2023
** my_strncpy
** File description:
** Copy n string from a string to another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    for (int i = 0; i < n; i += 1) {
        dest[i] = src[i];
    }
    return dest;
}
