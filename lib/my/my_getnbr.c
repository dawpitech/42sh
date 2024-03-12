/*
** EPITECH PROJECT, 2023
** my_getnbr
** File description:
** Return a number contained in a string passed as parameter
*/

static
int is_a_valid_number(char n)
{
    return (n >= '0' && n <= '9');
}

static
void edit_sign(int *negative_flag, const char *character)
{
    if (*character == '-') {
        if (*negative_flag == 0) {
            *negative_flag = 1;
        } else {
            *negative_flag = 0;
        }
        return;
    }
    if (*character == '+') {
        if (*negative_flag == 1) {
            return;
        }
        *negative_flag = 0;
    }
    return;
}

static
int safe_return(int rest, int is_neg)
{
    if (is_neg) {
        return rest;
    }
    if (rest > 0) {
        return (0);
    }
    rest = -rest;
    if (rest < 0) {
        return (0);
    }
    return rest;
}

static
int has_overflowed_checker(int rst)
{
    if (rst > 0) {
        return (1);
    } else {
        return (0);
    }
}

int my_getnbr(char const *str)
{
    int rst = 0;
    int is_negative = 0;
    int has_started = 0;
    int has_overflowed = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        edit_sign(&is_negative, &str[i]);
        if (has_overflowed)
            return (0);
        if (is_a_valid_number(str[i])) {
            has_started = 1;
            rst = (rst * 10) - (str[i] - 48);
            has_overflowed = has_overflowed_checker(rst);
            continue;
        }
        if (has_started)
            return safe_return(rst, is_negative);
    }
    return safe_return(rst, is_negative);
}
