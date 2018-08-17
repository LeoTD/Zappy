#include "server.h"
#include "player_type.h"

int		player_right(t_player *player)
{
	if (player->facing == NORTH)
		return (EAST);
	else if (player->facing == EAST)
		return (SOUTH);
	else if (player->facing == SOUTH)
		return (WEST);
	else
		return (NORTH);
}

int		player_forward(t_player *player)
{
	return (player->facing);
}
