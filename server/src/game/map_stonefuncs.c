#include "server.h"
#include "tile_type.h"
#include "player_type.h"

int				player_place_stone(int type, t_tile *t, t_player *player)
{
	assert(t != NULL);
	if (player->stones[type] < 1)
		return (1);
	player->stones[type] -= 1;
	t->stones[type] += 1;
	return (0);
}

/*
** Returns 0 on success.
** If requesting more stones than are present, returns 1.
*/

int				player_pickup_stone(int type, t_tile *t, t_player *player)
{
	assert(t != NULL);
	if (t->stones[type] < 1)
		return (1);
	t->stones[type] -= 1;
	player->stones[type] += 1;
	return (0);
}

void			remove_stones(int stones[6], t_tile *t)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		assert(t->stones[i] >= stones[i]);
		t->stones[i] -= stones[i];
		++i;
	}
}

int				place_stone(int type, t_tile *t)
{
	assert(t);
	t->stones[type] += 1;
	return (0);
}

int				place_random_stones(int type, int pool)
{
	while (pool-- > 0)
		place_stone(type, get_random_tile());
	return (0);
}
