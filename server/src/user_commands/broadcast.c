#include "server.h"

char	*broadcast(int player_id, void *args)
{
	(void)player_id;
	(void)args;
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return "placeholder";
}
