/*
** EPITECH PROJECT, 2023
** my_sort_int_array
** File description:
** Sort an integer array in ascending order
*/

#include "my.h"

static
void bubble_sort(int *array, int size)
{
    for (int i = 1; i < size; i += 1) {
        if (array[i - 1] > array[i]) {
            my_swap(&array[i - 1], &array[i]);
        }
    }
}

void my_sort_int_array(int *array, int size)
{
    for (int i = 1; i < size; i += 1) {
        bubble_sort(array, size);
    }
}
