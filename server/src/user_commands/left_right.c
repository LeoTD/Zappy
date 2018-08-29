#include "server.h"

char	*left(int player_id, void *args)
{
	(void)args;
	turn_left(get_player(player_id));
	return ("ok\n");
}

char	*right(int player_id, void *args)
{
	(void)args;
	turn_right(get_player(player_id));
	return ("ok\n");
}
