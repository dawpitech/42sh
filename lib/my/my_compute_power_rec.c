/*
** EPITECH PROJECT, 2023
** my_compute_power_rec
** File description:
** Recursive function that return n raised to the power of p
*/

#include "my.h"

int my_compute_power_rec(int nb, int p)
{
    if (p < 0) {
        return (0);
    }
    if (p == 0) {
        return (1);
    }
    if (p == 1) {
        return (nb);
    }
    return (nb * my_compute_power_rec(nb, p - 1));
}
