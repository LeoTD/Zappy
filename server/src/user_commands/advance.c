#include "server.h"

char	*advance(int player_id, void *args)
{
	move_player(player_id);
	return ("ok\n");
}
