/*
** EPITECH PROJECT, 2023
** my_str_islower
** File description:
** Return 1 if the string only contains alphabetical char and in low cases
*/

int my_str_islower(char const *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (!(str[i] >= 'a' && str[i] <= 'z')) {
            return (0);
        }
    }
    return (1);
}
