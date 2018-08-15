#include "server.h"

/*
**	Returns 0 if obj resource was successfully removed from player inventory and
**	placed onto map. Returns 1 otherwise.
*/

int		attempt_to_put(t_player *player, char *obj)
{
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

char	*put(int player_id, void *args)
{
	char		*obj_to_put;
	t_player	*player;

	obj_to_put = (char*)args;
	player = get_player(player_id);
	if (attempt_to_put(player, obj_to_put))
	{
		return ("ko\n");
	}
	return ("ok\n");
}
