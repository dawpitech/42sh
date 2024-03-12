/*
** EPITECH PROJECT, 2023
** my_compute_square_root
** File description:
** Return the square root of a whole number given as argument,
** if is no whole, return 0
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    int temp;

    if (nb <= 0) {
        return (0);
    }
    if (nb == 1) {
        return (1);
    }
    for (int i = 1; i <= nb; i += 1) {
        temp = my_compute_power_rec(i, 2);
        if (temp == nb) {
            return (i);
        }
        if (temp == 0 || temp > nb) {
            return (0);
        }
    }
    return (0);
}
