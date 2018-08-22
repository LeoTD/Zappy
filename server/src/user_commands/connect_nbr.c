#include "server.h"

char	*connect_nbr(int player_id, void *args)
{
	(void)player_id;
	(void)args;
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return "placeholder";
}
