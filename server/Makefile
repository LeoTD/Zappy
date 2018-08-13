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


# ---------------------------------------------------------------------------- #
# ----------- SRC/GAME ------------------------------------------------------- #
GAME_FILES	= map_creation.c \
			  map_player_movement.c \
			  map_tile_movement.c \
			  map_tile_to_player_funcs.c \
			  map_stonefuncs.c \
			  map_foodfuncs.c \
			  player_creation.c \
			  player_data_api.c \

GAME_SRC	= $(addprefix game/, $(GAME_FILES))

# ---------------------------------------------------------------------------- #
# ----------- SRC/USER_COMMANDS ---------------------------------------------- #
USRCMD_FILES= advance.c \

USRCMD_SRC	= $(addprefix user_commands/, $(USRCMD_FILES))

# Add source files here: (files assumed to be in ./src folder)
FILES		= message_to_command.c \
			  server.c \
			  user_commands.c \

# Add any subfolder SRC's here:
SRC			= $(addprefix src/, $(FILES) $(GAME_SRC) $(USRCMD_SRC))

# MAIN is used by		"make"
# TESTMAIN is used by	"make test"
# (Use full relative path to Makefile)
MAIN		= src/main.c

TESTMAIN	= test/testmain.c
TESTS		= $(wildcard test/test_*.c)

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

test: CFLAGS += -Wno-error -Wno-unused-parameter -Wno-unused-variable
test: $(SRC) $(INC) $(TESTMAIN)
	@printf "%b" "$(LIB_COLOR)Compiling Test: $(OK_COLOR)test_$(NAME)\n$(NO_COLOR)"
	@$(CC) $(DEBUG) $(CFLAGS) $(INC_FLAGS) -Itest -o test_$(NAME) $(TESTMAIN) $(TESTS) $(SRC)

norm:
	@printf "%b" "$(LIB_COLOR)$(NAME): Checking Norm...\n$(NO_COLOR)"
	@norminette $(SRC) $(INC) $(MAIN)

.PHONY: clean fclean all re test norm
