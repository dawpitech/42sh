/*
** EPITECH PROJECT, 2024
** B-CPE-110-BDX-1-1-secured-maxime.goyheneche
** File description:
** secured header
*/

#ifndef B_CPE_110_BDX_1_1_SECURED_MAXIME_GOYHENECHE_SECURED_H
    #define B_CPE_110_BDX_1_1_SECURED_MAXIME_GOYHENECHE_SECURED_H
    #define EXIT_FAILURE_TECH 84
typedef struct cell_content_s {
    unsigned int hashed_key;
    char *content;
    struct cell_content_s *next;
} cell_content_t;
int secured(int argc, char **argv);
#endif //B_CPE_110_BDX_1_1_SECURED_MAXIME_GOYHENECHE_SECURED_H
