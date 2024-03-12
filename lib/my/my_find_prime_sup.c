/*
** EPITECH PROJECT, 2023
** my_find_prime_sup
** File description:
** Return the smallest prime number greather then or equal
** to the number given as parameter
*/

#include "my.h"

int my_find_prime_sup(int nb)
{
    if (my_is_prime(nb) == 1) {
        return nb;
    } else {
        if (nb > 0 && nb + 1 < 0) {
            return (0);
        }
        return my_find_prime_sup(nb + 1);
    }
}
