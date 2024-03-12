##
## EPITECH PROJECT, 2023
## My Makefile
## File description:
## Makefile for mylib
##

CC	:=	gcc -std=gnu11

CFLAGS	=	-W
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wundef
CFLAGS	+=	-Wshadow
CFLAGS	+=	-Wunreachable-code
CLFAGS	+=	-Wmissing-prototypes
CFLAGS	+=	-pedantic
CFLAGS	+=	-g3
CFLAGS	+=	-I./include/

# ↓ BUILD DIR
BDIR	=	.build

VPATH = .
SRC = my_compute_power_rec.c
SRC += my_compute_square_root.c
SRC += memory_utils.c
SRC += extra_modifiers.c
SRC += my_putfloat.c
SRC += my_memset.c
SRC += my_find_prime_sup.c
SRC += my_getnbr.c
SRC += my_isneg.c
SRC += my_is_prime.c
SRC += my_putchar.c
SRC += my_putnbr_base.c
SRC += my_put_nbr.c
SRC += my_putstr.c
SRC += my_revstr.c
SRC += my_showmem.c
SRC += my_showstr.c
SRC += my_show_word_array.c
SRC += my_sort_int_array.c
SRC += my_strcapitalize.c
SRC += my_strcat.c
SRC += my_strcmp.c
SRC += my_strcpy.c
SRC += my_strdup.c
SRC += my_str_isalpha.c
SRC += my_str_islower.c
SRC += my_str_isnum.c
SRC += my_str_isprintable.c
SRC += my_str_isupper.c
SRC += my_strlen.c
SRC += my_strlowcase.c
SRC += my_strncat.c
SRC += my_strncmp.c
SRC += my_strncpy.c
SRC += my_strstr.c
SRC += my_str_to_word_array.c
SRC += my_strupcase.c
SRC += my_swap.c
SRC += my_printf.c
SRC += modifiers.c
SRC	+=	my_put_stderr.c

OBJ = $(SRC:%.c=$(BDIR)/%.o)

# ↓ Binairies name
NAME = libmy.a

all: $(NAME)

$(BDIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
	@ ar rc libmy.a $(OBJ)
	@ mkdir -p ../../include
	@ cp -r ./include/. ../../include/.
	@ cp  libmy.a ../

clean:
	@ rm -f $(OBJ)

fclean: clean
	@ rm -f $(NAME)
	@ rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
