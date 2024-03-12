/*
** EPITECH PROJECT, 2023
** mylib
** File description:
** my_put_stderr
*/

#include <unistd.h>

#include "./include/my.h"

/**
 * Print a string in the std error
 * @param str a message
 * @return the number of bytes written, -1 in case of errors
 */
ssize_t my_put_stderr(char const *str)
{
    int len = 0;

    if (str == NULL)
        return write(STDERR_FILENO, NULL_MSG, my_strlen(NULL_MSG));
    len = my_strlen(str);
    return write(STDERR_FILENO, str, len);
}
