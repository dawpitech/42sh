/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** mem_toolbox header
*/

#ifndef MINISHELL_MEM_TOOLBOX_H
    #define MINISHELL_MEM_TOOLBOX_H
void my_memcpy(void *dest, void *src, size_t size);
void *my_realloc(void *ptr, size_t new_size, size_t old_size);
ssize_t my_put_stderr(char const *str);
int print_error_with_input(char *input);
#endif //MINISHELL_MEM_TOOLBOX_H
