/*
** EPITECH PROJECT, 2023
** my_str_isprintable
** File description:
** Return 1 if the string only contains printable chars
*/

int my_str_isprintable(char const *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (!(str[i] >= 32 && str[i] <= 126)) {
            return (0);
        }
    }
    return (1);
}
