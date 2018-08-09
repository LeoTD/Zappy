#include "server.h"

int		test_user_commands_runnable(void)
{
	advance(1, NULL);
	left(1, NULL);
	right(1, NULL);
	see(1, NULL);
	inventory(1, NULL);
	take(1, "phiras");
	put(2, "phiras");
	kick(2, NULL);
	broadcast(2, "text");
	fork_player(2, NULL);
	connect_nbr(2, NULL);
	printf("%s: ok\n", __func__);
	return (0);
}
