#include "server.h"
#include "tile_type.h"

int test_stone_correctness(int type, int pool)
{
	int res = 0;

	for (int x = 0; x < g_map->dim.x; x++)
		for (int y = 0; y < g_map->dim.y; y++)
			if (g_map->tile[x][y].stones[type] > 0)
				res += g_map->tile[x][y].stones[type];
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

	pool = 30;
	place_random_food(pool);
	test_food_correctness(pool);
	place_random_stones(0, pool);
	test_stone_correctness(0, pool);
	place_random_stones(1, pool);
	test_stone_correctness(1, pool);
	place_random_stones(2, pool);
	test_stone_correctness(2, pool);
	place_random_stones(3, pool);
	test_stone_correctness(3, pool);
	place_random_stones(4, pool);
	test_stone_correctness(4, pool);
	place_random_stones(5, pool);
	test_stone_correctness(5, pool);
	printf("%s: ok\n", __FILE__);
	return (0);
}
