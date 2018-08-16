#include "server.h"
#include "player_type.h"

void	turn_right(int pid)
{
	t_player *player;

	player = get_player(pid);
	if (player->facing == NORTH)
		player->facing = EAST;
	else if (player->facing == EAST)
		player->facing = SOUTH;
	else if (player->facing == SOUTH)
		player->facing = WEST;
	else if (player->facing == WEST)
		player->facing = NORTH;
}

void	turn_left(int pid)
{
	t_player *player;

	player = get_player(pid);
	if (player->facing == NORTH)
		player->facing = WEST;
	else if (player->facing == WEST)
		player->facing = SOUTH;
	else if (player->facing == SOUTH)
		player->facing = EAST;
	else if (player->facing == EAST)
		player->facing = NORTH;
}

void	walk_forward(int pid)
{
	t_player *player;

	player = get_player(pid);
	move_player(player, player->facing);
}

/*
**	Find a way to be able to be able to know exactly what is being taken.
**	Returns 1 if no resource exists to take. Returns 0 if taken successfully.
*/

int		attempt_to_take(int pid, char *obj)
{
	t_player *player;

	player = get_player(pid);
	if (!strcmp(obj, "food"))
		return (pickup_food(player->tile, player));
	else if (!strcmp(obj, "linemate"))
		return (pickup_stone(LINEMATE, player->tile, player));
	else if (!strcmp(obj, "deraumere"))
		return (pickup_stone(DERAUMERE, player->tile, player));
	else if (!strcmp(obj, "sibur"))
		return (pickup_stone(SIBUR, player->tile, player));
	else if (!strcmp(obj, "mendiane"))
		return (pickup_stone(MENDIANE, player->tile, player));
	else if (!strcmp(obj, "phiras"))
		return (pickup_stone(PHIRAS, player->tile, player));
	else if (!strcmp(obj, "thystame"))
		return (pickup_stone(THYSTAME, player->tile, player));
	return (1);
}

/*
**	Returns 0 if obj resource was successfully removed from player inventory and
**	placed onto map. Returns 1 otherwise.
*/

int		attempt_to_put(int pid, char *obj)
{
	t_player *player;

	player = get_player(pid);
	if (!strcmp(obj, "food"))
		return (player_place_food(player->tile, player));
	else if (!strcmp(obj, "linemate"))
		return (player_place_stone(LINEMATE, player->tile, player));
	else if (!strcmp(obj, "deraumere"))
		return (player_place_stone(DERAUMERE, player->tile, player));
	else if (!strcmp(obj, "sibur"))
		return (player_place_stone(SIBUR, player->tile, player));
	else if (!strcmp(obj, "mendiane"))
		return (player_place_stone(MENDIANE, player->tile, player));
	else if (!strcmp(obj, "phiras"))
		return (player_place_stone(PHIRAS, player->tile, player));
	else if (!strcmp(obj, "thystame"))
		return (player_place_stone(THYSTAME, player->tile, player));
	return (1);
}
