#include "server.h"
#include "tile_type.h"
#include "player_type.h"

/*
** Low level functions for player placement and removal
** and player array handling per tile.
*/

int			grow_parray(t_tile *t)
{
	if ((t->players = realloc(t->players, sizeof(t_player *)
					* t->parray_size * 2)) == NULL)
		ERR_OUT("grow_parray; realloc");
	bzero(t->players + t->parray_size, t->parray_size * sizeof(t_player *));
	t->parray_size *= 2;
	return (0);
}

int			add_player_to_tile(t_player *p, t_tile *t)
{
	int			i;

	i = 0;
	if (!p || !t)
		ERR_OUT("add_player_to_tile; null tile/player");
	if (t->num_players + 1 > t->parray_size)
		grow_parray(t);
	while (i < t->parray_size && t->players[i] != NULL)
		i++;
	if (i == t->parray_size)
		ERR_OUT("add_player_to_tile; Uhhh, this should never happen. wtf.");
	t->players[i] = p;
	t->num_players++;
	p->tile = t;
	return (0);
}

int			remove_player_from_tile(t_player *p, t_tile *t)
{
	int			i;

	i = -1;
	while (++i < t->parray_size)
		if (t->players[i] == p)
			break ;
	if (i == t->parray_size)
		ERR_OUT("remove_player_from_tile; This shouldn't happen.");
	t->players[i] = NULL;
	t->num_players--;
	p->tile = NULL;
	return (0);
}

t_player	*is_player_on_tile(t_player *p, t_tile *t)
{
	int			i;

	i = -1;
	while (++i < t->parray_size)
		if (t->players[i] == p)
			break ;
	if (i == t->parray_size)
		return (0);
	else
		return (p);
}
