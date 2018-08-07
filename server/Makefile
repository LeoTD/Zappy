NAME		= server

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
INC_FLAGS	= -I inc

# -g for lldb
DEBUG		= #-g

# Cosmetics Section:
OK_COLOR	= \033[38;5;105;1m
OBJ_COLOR	= \033[38;5;208m
COM_COLOR	= \033[38;5;200m
LIB_COLOR	= \033[1;32m
NO_COLOR    = \033[m

COM_STRING	= "Compiling:"
# End Cosmetics.

# Add header files here: (use full relative path to Makefile)
INC			= inc/$(NAME).h \

# Add source files here: (files assumed to be in ./src folder)
FILES		= map_creation.c \
			  map_stonefuncs.c \
			  server.c \
			  user_commands.c \

# MAIN is used by		"make"
# TESTMAIN is used by	"make test"
# (Use full relative path to Makefile)
MAIN		= src/main.c

TESTMAIN	= test/testmain.c
TESTS		= $(wildcard test/test_*.c)

SRC			= $(addprefix src/, $(FILES))

# ---------------------------------------------------------------------------- #

all: $(SRC) $(INC) $(MAIN)
	@printf "%b" "$(LIB_COLOR)Compiling: $(OK_COLOR)$(NAME)\n$(NO_COLOR)"
	@$(CC) $(DEBUG) $(CFLAGS) $(INC_FLAGS) -o $(NAME) $(MAIN) $(SRC)
	@mv $(NAME) ../bin/

clean:
	@printf "Cleaning up $(NAME)...\n"

fclean: clean
	@rm -f ../bin/$(NAME)
	@rm -f test_$(NAME)

re: fclean all

test: CFLAGS += -Wno-error -Wno-unused-parameter
test: $(SRC) $(INC) $(TESTMAIN)
	printf "%b" "$(LIB_COLOR)Compiling Test: $(OK_COLOR)test_$(NAME)\n$(NO_COLOR)"
	$(CC) $(DEBUG) $(CFLAGS) $(INC_FLAGS) -Itest -o test_$(NAME) $(TESTMAIN) $(TESTS) $(SRC)

norm:
	@printf "%b" "$(LIB_COLOR)$(NAME): Checking Norm...\n$(NO_COLOR)"
	@norminette $(SRC) $(INC) $(MAIN)

.PHONY: clean fclean all re test norm
