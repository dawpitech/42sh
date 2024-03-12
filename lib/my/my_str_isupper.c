/*
** EPITECH PROJECT, 2023
** my_str_isupper
** File description:
** Return 1 if the string only contains alphabetical char and in upper cases
*/

int my_str_isupper(char const *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (!(str[i] >= 'A' && str[i] <= 'Z')) {
            return (0);
        }
    }
    return (1);
}
