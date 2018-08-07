
#include "server.h"

int				init_tile(t_tile *t, int x, int y)
{
	int			i;

	i = -1;
	t->x = x;
	t->y = y;
	t->players = NULL;
	t->num_players = 0;
	while (++i < 6)
		t->stones[i] = 0;
	t->food = 0;
	return (0);
}

int				create_map(int x, int y)
{
	int			i;
	int			k;

	i = -1;
	if ((g_map = malloc(sizeof(t_map_info))) == NULL)
		;//Error out!
	g_map->x = x;
	g_map->y = y;
	if ((g_map->tile = malloc(x * sizeof(t_tile *))) == NULL)
		;//Error out!
	while (++i < x)
		if ((g_map->tile[i] = malloc(y * sizeof(t_tile))) == NULL)
			;//Error out!
	i = -1;
	k = -1;
	while (++i < x)
	{
		while (++k < y)
		{
			init_tile(&g_map->tile[i][k], i, k);
		}
		k = -1;
	}
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
				if (random() % 10 == 0)
				{
					place_stone(type, 1, &g_map->tile[i][k]);
					pool--;
				}
			k = -1;
		}
		i = -1;
	}
	return (0);
}
