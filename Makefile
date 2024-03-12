##
## EPITECH PROJECT, 2023
## Minishell
## File description:
## Main Makefile of the project
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
CFLAGS	+=	-pedantic -g3
CFLAGS	+=	-I./include/

T_CFLAGS	:= $(CFLAGS)
T_CFLAGS	+=	-lcriterion
T_CFLAGS	+=	--coverage

LIBS_FLAGS	=	-L./lib/ -lmy -lhashtable

BDIR	=	.build
T_BDIR	=	.buildTests

NAME	=	mysh
T_NAME	=	unit_tests
SEGFAULT_NAME	=	segfault.bin
FP_EXECP_NAME	=	floating.bin

SRC = ./sources/minishell.c
SRC	+=	./sources/env/env_manager.c
SRC	+=	./sources/env/env_converter.c
SRC	+=	./sources/parser/my_parser.c
SRC	+=	./sources/builtins/builtins_cmd.c
SRC	+=	./sources/builtins/builtins_runner.c
SRC	+=	./sources/IO/prompt.c
SRC	+=	./sources/utils/mem_toolbox.c
SRC	+=	./sources/utils/my_put_stderr.c
SRC	+=	./sources/launcher/launcher.c
SRC	+=	./sources/launcher/path_explorer.c
SRC	+=	./sources/runner/runner.c
SRC	+=	./sources/parser/lexer.c

T_SRC	:=	$(SRC)
T_SRC	+=	./tests/my_tests.c

SRC	+=	./main.c

GCOVR_OUTPUT = gcovr

OBJ	=	$(SRC:%.c=$(BDIR)/%.o)
T_OBJ	=	$(T_SRC:%.c=$(T_BDIR)/%.o)

all:	$(NAME)

$(NAME):	build_lib $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIBS_FLAGS)

$(T_NAME):	fclean build_lib $(T_OBJ)
	$(CC) $(T_OBJ) $(T_CFLAGS) -o $(T_NAME) $(LIBS_FLAGS)

$(T_BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(T_CFLAGS)

$(BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

asan:	CFLAGS += -fsanitize=address,leak,undefined -g3
asan: re

debug:	CFLAGS	+=	-g3
debug: re

tests_run:	$(T_NAME)
	@ -./$(T_NAME)

tests_run_pp:	$(T_NAME)
	@ -./$(T_NAME) --verbose --full-stats --color=always -j8
	@ mkdir -p $(GCOVR_OUTPUT)
	@ gcovr --exclude=tests --html-details $(GCOVR_OUTPUT)/output.html

build_lib:
	@ make -C ./lib/my/
	@ make -C ./lib/hashtable/

clean:
	@ rm -f $(T_OBJ)
	@ rm -f $(OBJ)
	@ rm -rf $(T_BDIR)
	@ rm -rf $(BDIR)
	@ rm -rf $(GCOVR_OUTPUT)

fclean:	clean
	@ rm -f $(NAME)
	@ rm -f $(T_NAME)
	@ rm -f $(SEGFAULT_NAME)
	@ rm -f $(FP_EXECP_NAME)
	@ make -C ./lib/my/ fclean
	@ make -C ./lib/hashtable/ fclean

re:	fclean all

segfault:
	$(CC) bonus/segfault.c -o $(SEGFAULT_NAME)

floating:
	$(CC) bonus/fp_exception.c -o $(FP_EXECP_NAME)

.PHONY : all asan tests_run_pp tests_run build_lib clean fclean re segfault
.PHONY : floating debug
