#include "server.h"

int				player_place_stone(int type, t_tile *t, t_player *player)
{
	if (!t)
	{
		printf("Tried to place stone in NULL tile!\n");
		return (-1);
	}
	if (player->stones[type] < 1)
		return (1);
	player->stones[type] -= 1;
	t->stones[type] += 1;
	return (0);
}

int				place_stone(int type, t_tile *t)
{
	if (!t)
	{
		printf("Tried to place stone in NULL tile!\n");
		return (-1);
	}
	t->stones[type] += 1;
	return (0);
}

/*
** Returns 0 on success.
** If requesting more stones than are present, returns 1.
*/

int				pickup_stone(int type, t_tile *t, t_player *player)
{
	if (!t)
	{
		printf("Tried to remove stone from NULL tile!\n");
		return (-1);
	}
	if (t->stones[type] < 1)
		return (1);
	t->stones[type] -= 1;
	player->stones[type] += 1;
	return (0);
}

int				place_random_stones(int type, int pool)
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
					place_stone(type, &g_map->tile[i][k]);
			k = -1;
		}
		i = -1;
	}
	return (0);
}
