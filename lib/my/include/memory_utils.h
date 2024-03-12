/*
** EPITECH PROJECT, 2023
** memory_utils
** File description:
** title
*/

#pragma once

void free_struct(char *buf, parts_t parts);
const command_t *get_command(char *buf);
void search_for_combined(char *remain, int *i, va_list list, int *compteur);
