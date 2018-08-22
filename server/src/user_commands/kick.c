#include "server.h"

char	*kick(int player_id, void *args)
{
	(void)args;
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	if (attempt_to_kick(player_id) == -1)
		return ("ko\n");
	return ("ok\n");
}
