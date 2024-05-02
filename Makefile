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

BDIR	=	.build
T_BDIR	=	.buildTests

NAME	=	mysh
T_NAME	=	unit_tests
SEGFAULT_NAME	=	segfault.bin
FP_EXECP_NAME	=	floating.bin

SRC = ./sources/minishell.c
SRC	+=	./sources/builtins/builtins_cmd.c
SRC	+=	./sources/builtins/builtins_history.c
SRC	+=	./sources/builtins/builtins_search_history.c
SRC	+=	./sources/env/env_manager.c
SRC	+=	./sources/env/env_converter.c
SRC	+=	./sources/IO/prompt.c
SRC	+=	./sources/IO/history.c
SRC	+=	./sources/IO/path_explorer.c
SRC	+=	./sources/utils/my_put_stderr.c
SRC	+=	./sources/compute/compute_root.c
SRC	+=	./sources/compute/compute_semicolon.c
SRC	+=	./sources/compute/compute_and.c
SRC	+=	./sources/compute/compute_or.c
SRC	+=	./sources/compute/compute_pipe.c
SRC	+=	./sources/compute/compute_command.c
SRC +=	./sources/parser_ast/lexer.c
SRC +=	./sources/parser_ast/backtrack_lexer.c
SRC +=	./sources/parser_ast/lib_lexer/my_isparenthese.c
SRC +=	./sources/parser_ast/lib_lexer/my_is_operator.c
SRC +=	./sources/parser_ast/lib_lexer/my_isalpha_lexer.c
SRC +=	./sources/parser_ast/lib_lexer/my_isalphanum_lexer.c
SRC +=	./sources/parser_ast/lib_lexer/my_isand.c
SRC +=	./sources/parser_ast/lib_lexer/my_issemicol.c
SRC +=	./sources/parser_ast/lib_lexer/is_redirection.c
SRC +=	./sources/parser_ast/lib_lexer/my_ispipe.c
SRC +=	./sources/parser_ast/parser.c
SRC +=	./sources/parser_ast/utils/pipe_utils.c
SRC +=	./sources/parser_ast/utils/root_utils.c
SRC +=	./sources/parser_ast/utils/semicol_utils.c
SRC +=	./sources/parser_ast/utils/and_utils.c
SRC +=	./sources/parser_ast/utils/or_utils.c
SRC +=	./sources/parser_ast/utils/redirect_utils.c
SRC +=  ./sources/parser_ast/utils/handle_double_quote.c
SRC +=  ./sources/parser_ast/utils/handle_single_quote.c
SRC +=  ./sources/parser_ast/utils/handle_parenthese.c
SRC +=  ./sources/parser_ast/utils/handle_operator.c
SRC +=	./sources/parser_ast/memory_management_parser/free_parser_lexer.c
SRC +=	./sources/parser_ast/memory_management_parser/init_parser_struct.c

T_SRC	:=	$(SRC)
T_SRC	+=	./tests/my_tests.c

SRC	+=	./main.c

GCOVR_OUTPUT = gcovr

OBJ	=	$(SRC:%.c=$(BDIR)/%.o)
T_OBJ	=	$(T_SRC:%.c=$(T_BDIR)/%.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(T_NAME):	fclean $(T_OBJ)
	$(CC) $(T_OBJ) $(T_CFLAGS) -o $(T_NAME)

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

re:	fclean all

segfault:
	$(CC) bonus/segfault.c -o $(SEGFAULT_NAME)

floating:
	$(CC) bonus/fp_exception.c -o $(FP_EXECP_NAME)

.PHONY : all asan tests_run_pp tests_run clean fclean re segfault floating
.PHONY : debug
