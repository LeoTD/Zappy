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
			  inc/command_type.h \
			  inc/command_list_type.h \
			  inc/command_queue_type.h \
			  inc/tile_type.h \
			  inc/player_type.h \
			  inc/client_type.h \
			  inc/fork_player.h \

# ---------------------------------------------------------------------------- #
# ----------- SRC/GAME ------------------------------------------------------- #
GAME_FILES	= map_creation.c \
			  player_movement.c \
			  tile_data_api.c \
			  map_tile_movement.c \
			  map_tile_to_player_funcs.c \
			  map_stonefuncs.c \
			  map_foodfuncs.c \
			  player_actions.c \
			  player_creation.c \
			  player_death.c \
			  player_data_api.c \
			  player_data_api_2.c \
			  player_empty_list_funcs.c \
			  game_init.c \
			  game_upkeep.c \
			  inventory.c \
			  str_utils.c \
			  find_resources.c \
			  resource_spawning.c \
			  levelups_and_gameovers.c \
			  direction.c \



GAME_SRC	= $(addprefix game/, $(GAME_FILES))

# ---------------------------------------------------------------------------- #
# ----------- SRC/USER_COMMANDS ---------------------------------------------- #
USRCMD_FILES= advance.c \
			  broadcast.c \
			  connect_nbr.c \
			  fork_player.c \
			  incantation.c \
			  inventory.c \
			  kick.c \
			  take.c \
			  left_right.c \
			  put.c \
			  see.c 

USRCMD_SRC	= $(addprefix user_commands/, $(USRCMD_FILES))

# Add source files here: (files assumed to be in ./src folder)
FILES		= active_socket_info.c \
			  cmdfunc_type.c \
			  command_type.c \
			  command_line_options.c \
			  command_list_type.c \
			  command_queue_type.c \
			  listen_for_connections.c \
			  receive_user_message.c \
			  user_clients_lookup.c \
			  handshake.c \
			  decrement_user_command_timers.c \
			  execute_command_list.c \
			  remove_dead_players.c \
			  game_over.c \
			  send_stringified_responses.c \
			  time_to_tick.c \
			  dequeue_commands.c \
			  client_type.c \
			  ascii_visuals.c \
			  hatch_queue.c \

# Add any subfolder SRC's here:
SRC			= $(addprefix src/, $(FILES) $(GAME_SRC) $(USRCMD_SRC))

# MAIN is used by		"make"
# TESTMAIN is used by	"make test"
# (Use full relative path to Makefile)
MAIN		= src/server.c

TESTMAIN	= test/testmain.c
TESTS		= $(wildcard test/test_*.c) test/helpers.c

# ---------------------------------------------------------------------------- #

all: $(NAME)

$(NAME): $(SRC) $(INC) $(MAIN)
	@mkdir -p ../bin
	@printf "%b" "$(LIB_COLOR)Compiling: $(OK_COLOR)$(NAME)\n$(NO_COLOR)"
	@$(CC) $(DEBUG) $(CFLAGS) $(INC_FLAGS) -o $(NAME) $(MAIN) $(SRC)
	@cp $(NAME) ../bin/

clean:
	@printf "Cleaning up $(NAME)...\n"

fclean: clean
	@rm -f ../bin/$(NAME)
	@rm -f test_$(NAME)
	@rm -f $(NAME)

re: fclean all

test: CFLAGS += -Wno-error -Wno-unused-parameter -Wno-unused-variable
test: test_$(NAME)
test_$(NAME): $(SRC) $(INC) $(TESTMAIN) $(TESTS)
	@printf "%b" "$(LIB_COLOR)Compiling Test: $(OK_COLOR)test_$(NAME)\n$(NO_COLOR)"
	@$(CC) $(DEBUG) $(CFLAGS) $(INC_FLAGS) -Itest -o test_$(NAME) $(TESTMAIN) $(TESTS) $(SRC)

norm:
	@printf "%b" "$(LIB_COLOR)$(NAME): Checking Norm...\n$(NO_COLOR)"
	@norminette $(SRC) $(INC) $(MAIN)

dev: CFLAGS += -Wno-error
dev: all

ascii: CFLAGS += -DASCII_ANIMATIONS
ascii: dev

.PHONY: clean fclean all re test norm dev ascii
