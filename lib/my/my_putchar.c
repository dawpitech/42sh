/*
** EPITECH PROJECT, 2023
** mylib
** File description:
** my_putchar
*/

#include <unistd.h>

/**
 * Write a char in the std out
 * @param c char
 * @return the number of bytes written, -1 in case of errors
 */
ssize_t my_putchar(char const c)
{
    return write(1, &c, 1);
}
