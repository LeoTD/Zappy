NAME		= Zappy

# Cosmetics Section:
OK_COLOR	= \033[38;5;105;1m
OBJ_COLOR	= \033[38;5;208m
COM_COLOR	= \033[38;5;200m
LIB_COLOR	= \033[1;32m
NO_COLOR    = \033[m

COM_STRING	= "Compiling:"
# End Cosmetics.

# ---------------------------------------------------------------------------- #

all: bin server client gfx

server:
	@make -C server

client:
	@make -C client

gfx:
	@make -C gfx

bin:
	@printf "Creating bin/ directory...\n"
	@mkdir bin/

clean:
	@printf "Cleaning up $(NAME)...\n"

fclean: clean
	@rm -rf bin
	@make -C server fclean
	@make -C client fclean
	@make -C gfx fclean

test:
	@make -C server test
	@make -C client test
	@make -C gfx test

re: fclean all

norm:
	@printf "%b" "$(LIB_COLOR)$(NAME): Checking Norm...\n$(NO_COLOR)"
	@make -C server norm
	@make -C client norm
	@make -C gfx norm

.PHONY: clean fclean all re server client gfx
