#include "server.h"

char	*kick(int player_id, void *args)
{
	if (attempt_to_kick(player_id) == -1)
		return ("ko\n");
	return ("ok\n");
}
