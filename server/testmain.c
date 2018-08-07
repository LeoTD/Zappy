
#include "server.h"
#include <stdio.h>

void			print_map_info(void)
{
	t_tile		*t;
	int			x, y;

	x = -1;
	y = -1;
	while (++x < g_map->x)
	{
		while (++y < g_map->y)
		{
			t = &g_map->tile[x][y];
			printf("(%d, %d)", t->x, t->y);
			printf(" \tStones: [  %d,  %d,  %d,  %d,  %d,  %d ]", t->stones[0], t->stones[1], t->stones[2], t->stones[3], t->stones[4], t->stones[5]);
		//	printf(" Food: [ %d ] Players: %d", t->food, t->num_players);
			printf("\n");
		}
		y = -1;
	}
}

int				main(void)
{
	create_map(10, 10);
	place_random_stones(0, 30);
	place_random_stones(1, 30);
	place_random_stones(2, 30);
	place_random_stones(3, 30);
	place_random_stones(4, 30);
	place_random_stones(5, 30);
	print_map_info();
	return (0);
}
