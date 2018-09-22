#include "server.h"
#include "player_type.h"
#include "tile_type.h"

/*
** Takes pid to get reference to a tile.
** Puts the count of players on that tile in [ *count ]
** malloc's a new int[] with pids of players on the tile.
*/

int			*get_current_tile_player_count(int pid, int *count)
{
	t_player		*p;
	t_tile			*t;
	int				i;
	int				j;
	int				*res;

	p = get_player(pid);
	t = p->tile;
	*count = t->count[PLAYERS];
	if ((res = malloc(sizeof(int *) * t->count[PLAYERS])) == NULL)
		ERR_OUT("get_current_tile_player_count; malloc");
	i = -1;
	j = -1;
	while (++i < t->count[PLAYERS])
	{
		assert(t->players[i] != NULL);
		res[++j] = t->players[i]->id;
	}
	return (res);
}

int			*get_current_tile_stones(int pid)
{
	t_player		*p;
	t_tile			*t;
	int				*res;

	p = get_player(pid);
	t = p->tile;
	res = malloc(sizeof(t->count));
	memcpy(res, t->count, sizeof(t->count));
	return (res);
}
