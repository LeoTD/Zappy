#include "server.h"

#define OK_COLOR "\033[1;35m"

void			print_map(void);

void			print_map_info(void)
{
	t_tile		*t;
	int			x, y;

	x = -1;
	y = -1;
	while (++x < g_map->dim.x)
	{
		while (++y < g_map->dim.y)
		{
			t = &g_map->tile[x][y];
			printf("(%d, %d)", t->x, t->y);
			printf(" \tStones: [  %d,  %d,  %d,  %d,  %d,  %d ]", t->stones[0], t->stones[1], t->stones[2], t->stones[3], t->stones[4], t->stones[5]);
			printf(" Food: [ %d ] Players: %d", t->food, t->num_players);
			printf("\n");
		}
		y = -1;
	}
}

int test_stone_correctness(int type, int pool)
{
	int res = 0;

	for (int x = 0; x < g_map->dim.x; x++)
		for (int y = 0; y < g_map->dim.y; y++)
			if (g_map->tile[x][y].stones[type] > 0)
				res += g_map->tile[x][y].stones[type];
//	printf("type: %d; pool: %d; res: %d\n", type, pool, res);
	assert(res == pool);
	return (0);
}

int test_food_correctness(int pool)
{
	int res = 0;

	for (int x = 0; x < g_map->dim.x; x++)
		for (int y = 0; y < g_map->dim.y; y++)
			if (g_map->tile[x][y].food > 0)
				res += g_map->tile[x][y].food;
//	printf("type: %d; pool: %d; res: %d\n", type, pool, res);
	assert(res == pool);
	return (0);
}

int	test_map_creation(void)
{
	int			pool;

	create_map(10, 10);
	for (int x = 0; x < g_map->dim.x; x++)
		for (int y = 0; y < g_map->dim.y; y++)
			assert(g_map->tile[x][y].x == x && g_map->tile[x][y].y == y);
	printf("%s[ OK ] \033[0m                                   Map tiles created!\n", OK_COLOR);

	pool = 30;
	place_random_food(pool);
	test_food_correctness(pool);
	printf("%s[ OK ] \033[0m                                   Map populated with food!\n", OK_COLOR);

	pool = 30;
	place_random_stones(0, pool);
	test_stone_correctness(0, pool);
	printf("%s[ OK ] ", OK_COLOR);
	place_random_stones(1, pool);
	test_stone_correctness(1, pool);
	printf("%s[ OK ] ", OK_COLOR);
	place_random_stones(2, pool);
	test_stone_correctness(2, pool);
	printf("%s[ OK ] ", OK_COLOR);
	place_random_stones(3, pool);
	test_stone_correctness(3, pool);
	printf("%s[ OK ] ", OK_COLOR);
	place_random_stones(4, pool);
	test_stone_correctness(4, pool);
	printf("%s[ OK ] ", OK_COLOR);
	place_random_stones(5, pool);
	test_stone_correctness(5, pool);
	printf("%s[ OK ] ", OK_COLOR);
	printf("\033[0mMap populated with stones!\n");
//	print_map_info();
//	print_map();
	return (0);
}
