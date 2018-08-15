#include "server.h"

/*
**	Returns 0 if obj resource was successfully removed from player inventory and
**	placed onto map. Returns 1 otherwise.
*/

int		attempt_to_put(t_player *player, char *obj)
{
	if (obj == "food")
		return (player_place_food(player->tile, player));
	else if (obj == "linemate")
		return (player_place_stone(LINEMATE, player->tile, player);
	else if (obj == "deraumere")
		return (player_place_stone(DERUAMERE, player->tile, player);
	else if (obj == "sibur")
		return (player_place_stone(SIBUR, player->tile, player);
	else if (obj == "mendiane")
		return (player_place_stone(MENDIANE, player->tile, player);
	else if (obj == "phiras")
		return (player_place_stone(PHIRAS, player->tile, player);
	else if (obj == "thystame")
		return (player_place_stone(THYSTAME, player->tile, player);
	return (1);
}

char	*put(int player_id, void *args)
{
	char		*obj_to_put;
	t_player	*player;

	obj = (char*)args;
	player = get_player(player_id);
	if (attempt_to_put(player, obj))
	{
		return ("ko\n");
	}
	return ("ok\n");
}
