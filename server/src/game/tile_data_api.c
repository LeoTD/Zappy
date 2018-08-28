#include "server.h"
#include "player_type.h"
#include "tile_type.h"

/*
void		tile_get_data(t_vec pos, t_tile_data *ret)
{
	t_tile		*t;

	t = &g_map->tile[pos.x][pos.y];
	ret->pos.x = pos.x;
	ret->pos.y = pos.y;
	ret->stones[0] = t->stones[0];
	ret->stones[1] = t->stones[1];
	ret->stones[2] = t->stones[2];
	ret->stones[3] = t->stones[3];
	ret->stones[4] = t->stones[4];
	ret->stones[5] = t->stones[5];
	ret->food = t->food;
	ret->num_players = t->num_players;
}
*/

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
	*count = t->num_players;
	if ((res = malloc(sizeof(int *) * t->num_players)) == NULL)
		ERR_OUT("get_current_tile_player_count; malloc");
	i = -1;
	j = -1;
	while (++i < t->parray_size)
		if (t->players[i] != NULL)
			res[++j] = t->players[i]->id;
	return (res);
}

int			*get_current_tile_stones(int pid)
{
	t_player		*p;
	t_tile			*t;
	int				*res;

	p = get_player(pid);
	t = p->tile;
	if ((res = malloc(sizeof(int) * 6)) == NULL)
		ERR_OUT("get_current_tile_stones; malloc");
	memcpy(res, t->stones, sizeof(t->stones));
	return (res);
}
