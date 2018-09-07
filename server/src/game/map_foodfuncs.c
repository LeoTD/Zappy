#include "server.h"
#include "tile_type.h"
#include "player_type.h"

int				player_place_food(t_tile *t, t_player *player)
{
	assert(t != NULL);
	if (player->food < 1)
		return (1);
	player->food -= 1;
	t->food += 1;
	return (0);
}

int				place_food(t_tile *t)
{
	assert(t != NULL);
	t->food += 1;
	return (0);
}

int				pickup_food(t_tile *t, t_player *player)
{
	assert(t != NULL);
	if (t->food < 1)
		return (1);
	t->food -= 1;
	player->food += 1;
	return (0);
}
