#include "server.h"
#include "player_type.h"

int		relative_west(int dir);
int		relative_east(int dir);
int		relative_south(int dir);

int		get_relative_direction(int pid, int direction)
{
	t_player	*player;

	player = get_player(pid);
	if (player->facing == EAST)
		return (relative_east(direction));
	if (player->facing == WEST)
		return (relative_west(direction));
	if (player->facing == SOUTH)
		return (relative_south(direction));
	return (direction);
}

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
		printf("Error: player facing invalid direction\n");
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
