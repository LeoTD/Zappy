#include "server.h"

char	*left(int player_id, void *args)
{
	t_player *player;

	player = get_player(player_id);
	if (player->facing == NORTH)
		player->facing = WEST;
	else if (player->facing == WEST)
		player->facing = SOUTH;
	else if (player->facing == SOUTH)
		player->facing = EAST;
	else if (player->facing == EAST)
		player->facing = NORTH;
	return ("ok\n");
}

char	*right(int player_id, void *args)
{
	t_player *player;

	player = get_player(player_id);
	if (player->facing == NORTH)
		player->facing = EAST;
	else if (player->facing == EAST)
		player->facing = SOUTH;
	else if (player->facing == SOUTH)
		player->facing = WEST;
	else if (player->facing == WEST)
		player->facing = NORTH;
	return ("ok\n");
}
