/*
** EPITECH PROJECT, 2023
** my_memset
** File description:
** memset
*/

#include "include/my.h"

void my_memset(void *buf, int val, long size)
{
    for (long s = 0; s < size; s++)
        ((char *)buf)[s] = val;
}
