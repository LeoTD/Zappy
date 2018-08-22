#include "server.h"

char	*fork_player(int player_id, void *args)
{
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return "placeholder";
}
