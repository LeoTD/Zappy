#include "server.h"

char	*advance(int player_id, void *args)
{
	(void)args;
	walk_forward(player_id);
	return ("ok\n");
}
