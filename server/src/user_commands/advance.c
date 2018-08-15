#include "server.h"

char	*advance(int player_id, void *args)
{
	t_player *player;

	player = get_player(player_id);
	move_player(player, player->facing);
	return ("ok\n");
}
