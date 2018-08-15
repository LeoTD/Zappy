#include "server.h"

/*
**	Find a way to be able to be able to know exactly what is being taken.
**	Returns 1 if no resource exists to take. Returns 0 if taken successfully.
*/

int		attempt_to_take(t_player *player, char *obj)
{
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

char	*take(int player_id, void *args)
{
	char		*obj_to_take;
	t_player	*player;

	obj_to_take = (char*)args;
	player = get_player(player_id);
	if (attempt_to_take(player, obj_to_take))
	{
		return ("ko\n");
	}
	return ("ok\n");
}
