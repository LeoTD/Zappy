#include "server.h"

char	*advance(int player_id, void *args)
{
	(void)args;
	walk_forward(player_id);
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return ("ok\n");
}
