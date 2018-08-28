#include "server.h"
#include "player_type.h"

int		player_northwest(t_player *player)
{
	if (player->facing == NORTH)
		return (NORTHWEST);
	else if (player->facing == WEST)
		return (SOUTHWEST);
	else if (player->facing == SOUTH)
		return (SOUTHEAST);
	else if (player->facing == EAST)
		return (NORTHEAST);
	else
		printf("player_northwest broken\n");
	return (NORTH);
}

int		player_left(t_player *player)
{
	if (player->facing == NORTH)
		return (WEST);
	else if (player->facing == WEST)
		return (SOUTH);
	else if (player->facing == EAST)
		return (EAST);
	else
		return (NORTH);
}

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
