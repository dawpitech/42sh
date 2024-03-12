/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** my_put_stderr header
*/

#ifndef MINISHELL_MY_PUT_STDERR_H
    #define MINISHELL_MY_PUT_STDERR_H
    #include <sys/types.h>
ssize_t my_put_stderr(char const *str);
int print_error_with_input(char *input);
#endif //MINISHELL_MY_PUT_STDERR_H
