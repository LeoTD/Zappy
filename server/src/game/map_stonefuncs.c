#include "server.h"
#include "tile_type.h"
#include "player_type.h"

int				player_place_stone(int type, t_tile *t, t_player *player)
{
	assert(t != NULL);
	if (player->count[type] < 1)
		return (1);
	player->count[type] -= 1;
	t->count[type] += 1;
	return (0);
}

/*
** Returns 0 on success.
** If requesting more stones than are present, returns 1.
*/

int				player_pickup_stone(int type, t_tile *t, t_player *player)
{
	assert(t != NULL);
	if (t->count[type] < 1)
		return (1);
	t->count[type] -= 1;
	player->count[type] += 1;
	return (0);
}

int				place_stone(int type, t_tile *t)
{
	assert(t);
	t->count[type] += 1;
	return (0);
}

int				place_random_stones(int type, int pool)
{
	while (pool-- > 0)
		place_stone(type, get_random_tile());
	return (0);
}
