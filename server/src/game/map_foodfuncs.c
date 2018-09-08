#include "server.h"
#include "tile_type.h"
#include "player_type.h"

int				player_place_food(t_tile *t, t_player *player)
{
	assert(t != NULL);
	if (player->count[FOOD] < 1)
		return (1);
	player->count[FOOD] -= 1;
	t->count[FOOD] += 1;
	return (0);
}

int				place_food(t_tile *t)
{
	assert(t != NULL);
	t->count[FOOD] += 1;
	return (0);
}

int				pickup_food(t_tile *t, t_player *player)
{
	assert(t != NULL);
	if (t->count[FOOD] < 1)
		return (1);
	t->count[FOOD] -= 1;
	player->count[FOOD] += 1;
	return (0);
}
