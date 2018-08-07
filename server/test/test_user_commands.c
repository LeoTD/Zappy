#include "server.h"

int		test_user_commands_runnable(void)
{
	advance(1, NULL);
	turn(1, "right");
	turn(1, "left");
	see(1, NULL);
	inventory(1, NULL);
	take(1, "phiras");
	put(2, "phiras");
	kick(2, NULL);
	broadcast(2, "text");
	fork_player(2, NULL);
	connect_nbr(2, NULL);
	puts("user commands ran without crashing");
	return (0);
}
