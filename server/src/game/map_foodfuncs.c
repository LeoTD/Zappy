#include "server.h"
#include "tile_type.h"
#include "player_type.h"

int				player_place_food(t_tile *t, t_player *player)
{
	if (!t)
	{
		printf("Tried to place food in NULL tile!\n");
		return (-1);
	}
	if (player->food < 1)
		return (1);
	player->food -= 1;
	t->food += 1;
	return (0);
}

int				place_food(t_tile *t)
{
	if (!t)
	{
		printf("Tried to place food in NULL tile!\n");
		return (-1);
	}
	t->food += 1;
	return (0);
}

/*
** Returns 0 on success.
** If requesting more food than is present, returns 1.
*/

int				pickup_food(t_tile *t, t_player *player)
{
	if (!t)
	{
		printf("Tried to remove food from NULL tile!\n");
		return (-1);
	}
	if (t->food < 1)
		return (1);
	t->food -= 1;
	player->food += 1;
	return (0);
}

int				place_random_food(int pool)
{
	while (pool-- > 0)
		place_food(get_random_tile());
	return (0);
}
