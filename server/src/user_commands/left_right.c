#include "server.h"

char	*left(int player_id, void *args)
{
	(void)args;
	turn_left(player_id);
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return ("ok\n");
}

char	*right(int player_id, void *args)
{
	(void)args;
	turn_right(player_id);
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return ("ok\n");
}
