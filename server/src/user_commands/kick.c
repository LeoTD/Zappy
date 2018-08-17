#include "server.h"

char	*kick(int player_id, void *args)
{
	if (attempt_to_kick(player_id))
		return ("ko\n");
	return ("ok\n");
}
