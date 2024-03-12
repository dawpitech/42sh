/*
** EPITECH PROJECT, 2023
** My Header
** File description:
** Header of mylib
*/

#ifndef LIBMY
    #define LIBMY
    #include <sys/types.h>
    #define IS_LOW(c) ((c >= 'a' && c <= 'z') ? (1) : (0))
    #define IS_UP(c) ((c >= 'A' && c <= 'Z') ? (1) : (0))
    #define IS_ALPHA(c) ((IS_LOW(c) || IS_UP(c)) ? (1) : (0))
    #define IS_NUM(c) ((c >= '0' && c <= '9') ? (1) : (0))
    #define IS_ALPHANUM(c) ((IS_ALPHA(c) || IS_NUM(c)) ? (1) : (0))
    #define ABS(c) (((c) > 0) ? (c) : (- (c)))
    #define POS(c) ((c > 0) ? (c) : (0))
    #define NULL_MSG "(NULL)"

int nbr_len(long long nb);
int my_putfloat(double nb, int precision);
void my_memset(void *buf, int val, long size);
char **my_str_to_word_array(char const *);
int my_compute_power_rec(int, int);
int my_compute_square_root(int);
int my_find_prime_sup(int);
int my_getnbr(char const *);
int my_isneg(int);
int my_is_prime(int);
ssize_t my_putchar(char const c);
int my_put_nbr(long nb);
int my_putstr(char const *);
char *my_revstr(char *);
int my_showmem(char const *, int);
int my_showstr(char const *);
void my_sort_int_array(int *, int);
char *my_strcapitalize(char *);
char *my_strcat(char *, char const *);
int my_strcmp(char const *, char const *);
char *my_strcpy(char *, char const *);
int my_str_isalpha(char const *);
int my_str_islower(char const *);
int my_str_isnum(char const *);
int my_str_isprintable(char const *);
int my_str_isupper(char const *);
int my_strlen(char const *);
char *my_strlowcase(char *);
char *my_strncat(char *, char const *, int);
int my_strncmp(char const *, char const *, int);
char *my_strncpy(char *, char const *, int);
char *my_strstr(char *, char const *);
char *my_strupcase(char *);
void my_swap(int *, int *);
int my_show_word_array(char *const *);
char *my_strdup(char const *);
int my_putnbr_base(long long nb, char **base);
ssize_t my_put_stderr(char const *str);
#endif
