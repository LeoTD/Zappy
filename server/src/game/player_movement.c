#include "server.h"

/*
** Removes the player from their current tile and places them on
** the adjacent tile in the direction specified by [ dir ]
**
** Common usage: move_player(p, p->facing);
*/

int			move_player(int pid)
{
	t_tile		*next;
	t_player	*player;

	player = get_player(pid);
	next = get_adj_tile(player->tile, player->facing);
	remove_player_from_tile(player, player->tile);
	add_player_to_tile(player, next);
	player->tile = next;
	return (0);
}
