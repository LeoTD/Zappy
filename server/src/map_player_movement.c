#include "server.h"

/*
** Removes the player from their current tile and places them on
** the adjacent tile in the direction specified by [ dir ]
**
** Common usage: move_player(p, p->facing);
*/

int			move_player(t_player *p, int dir)
{
	t_tile		*next;

	next = get_adj_tile(p->tile, dir);
	remove_player_from_tile(p, p->tile);
	add_player_to_tile(p, next);
	p->tile = next;
	return (0);
}
