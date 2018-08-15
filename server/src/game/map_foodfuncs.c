#include "server.h"

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
	int			i;
	int			k;

	i = -1;
	k = -1;
	while (pool > 0)
	{
		while (++i < g_map->x)
		{
			while (++k < g_map->y)
				if (random() % 10 == 0 && --pool >= 0)
					place_food(&g_map->tile[i][k]);
			k = -1;
		}
		i = -1;
	}
	return (0);
}
