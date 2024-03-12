/*
** EPITECH PROJECT, 2023
** my_swap
** File description:
** Swap the content of 2 integers
*/

void my_swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}
