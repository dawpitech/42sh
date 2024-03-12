##
## EPITECH PROJECT, 2023
## Hashtable
## File description:
## Makefile of Hashtable lib
##

CC	:=	gcc -std=gnu11

CFLAGS	=	-W
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wundef
CFLAGS	+=	-Wshadow
CFLAGS	+=	-Wunreachable-code
CFLAGS	+=	-Wmissing-prototypes
CFLAGS	+=	-Wno-unknown-pragmas
CFLAGS	+=	-pedantic
CFLAGS	+=	-I./include/

BDIR	=	.build

LDFLAGS	=	-L. -lhashtable

NAME	=	libhashtable.a

SRC	=	my_hash.c
SRC	+=	hashtable_generator.c
SRC	+=	hashtable_dumper.c
SRC	+=	hashtable_content_manager.c
SRC	+=	int_utils.c
SRC	+=	hashtable_destroyer.c
SRC	+=	str_utils.c

OBJ	=	$(SRC:%.c=$(BDIR)/%.o)
OBJ_EXE	=	$(SRC_EXE:%.c=$(BDIR_EXE)/%.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	@ ar rc $(NAME) $(OBJ)
	@ mkdir -p ../../include
	@ cp -r ./include/. ../../include/.
	@ cp $(NAME) ../.

$(BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@ rm -f $(OBJ)

fclean:	clean
	@ rm -f $(NAME)
	@ rm -f ../$(NAME)

re:	fclean all

.PHONY : all clean fclean re
