/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** my_tests header
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../include/minishell.h"

extern char** environ;

Test(fonctionnal, echo, .init=cr_redirect_stdout) {
    FILE *fp;
    char output[4096];

    fp = popen("tcsh -c \"echo bob\"", "r");
    if (fp == NULL)
        cr_assert_fail("popen failed");
    if (fgets(output, 4096 - 1, fp) == NULL) {
        pclose(fp);
        cr_assert_fail("fgets failed");
    }
    pclose(fp);
    output[strlen(output) - 1] = '\n';
    minishell(3, (char *[3]){"./42sh", "-c", "echo \"bob\""}, environ);
    cr_assert_stdout_eq_str(output);
}

Test(functionnal, echo_and_history, .init=cr_redirect_stdout) {
    cr_assert_eq(0, minishell(3,
        (char *[3]){"./42sh", "-c", "echo \"bob\"; history"}, environ));
}

Test(fonctionnal, ls, .init=cr_redirect_stdout) {
    FILE *fp;
    char output[4096] = {0};
    char buffer[4096] = {0};

    fp = popen("tcsh -c ls", "r");
    if (fp == NULL)
        cr_assert_fail("popen failed");
    while (fgets(buffer, 4096 - 1, fp) != NULL) {
        strcat(output, buffer);
    }
    pclose(fp);
    minishell(3, (char *[3]){"./42sh", "-c", "ls"}, environ);
    cr_assert_stdout_eq_str(output);
}
