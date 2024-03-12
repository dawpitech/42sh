/*
** EPITECH PROJECT, 2024
** B-CPE-110-BDX-1-1-secured-maxime.goyheneche
** File description:
** my_hash header
*/

#include <stddef.h>

#include "my_hash.h"
#include "hashtable.h"

static
unsigned int str_to_int(char const *str)
{
    int number = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i] != '\0'; i += 1){
        number = (number * DECIMAL) + str[i];
    }
    return number;
}

static
unsigned int middle_square(unsigned int const key)
{
    return key * key / HASH_DIVIDE_PARAM % HASH_MODULO_PARAM;
}

int hash(char *key, __attribute__((unused)) int len)
{
    unsigned int key_int;

    key_int = str_to_int(key);
    for (int x = 0; x < HASH_PASSES; ++x) {
        key_int = middle_square(key_int);
    }
    if ((int) key_int < 0)
        key_int = key_int * -1;
    return (int) key_int;
}
