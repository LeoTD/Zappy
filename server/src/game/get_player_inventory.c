#include "server.h"
#include "player_type.h"
/*
**	Example end string: {food 356, linemate 2, draumere 3, sibur 4, mendiane 5, ...}
**	
*/

char	*search_inventory(t_player *player)
{
	char	*all;
	char	*item_and_count;
	
	item_and_count = strnew("");
	item_and_count = find_food(player->tile);
	return (NULL);
}

char	*get_player_inventory(int pid)
{
	char		*inventory;
	t_player	*player;

	player = get_player(pid);
	inventory = NULL;
	//	inventory = search_inventory(player);
	return (inventory);

}
