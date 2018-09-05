#include "server.h"
#include "tile_type.h"

#define LINEMATE_CHANCE 9
#define DERAUMERE_CHANCE 8
#define SIBUR_CHANCE 10
#define MENDIANE_CHANCE 5
#define PHIRAS_CHANCE 6
#define THYSTAME_CHANCE 1
#define FOOD_CHANCE 28
#define SUM_RESOURCE_CHANCES (LINEMATE_CHANCE + DERAUMERE_CHANCE + SIBUR_CHANCE + MENDIANE_CHANCE + PHIRAS_CHANCE + THYSTAME_CHANCE + FOOD_CHANCE)
#define SPAWN_CHANCE_NUMERATOR 1
#define SPAWN_CHANCE_DENOMINATOR 600
#define PREGAME_RESOURCE_SPAWNING_ROUNDS 1000

void	spawn_random_resource_on_tile(t_tile *t)
{
	unsigned int	r;
	unsigned int	accumulator;

	accumulator = 0;
	r = random() % SUM_RESOURCE_CHANCES;
	if (r < (accumulator += FOOD_CHANCE))
		t->food += 1;
	else if (r < (accumulator += LINEMATE_CHANCE))
		place_stone(LINEMATE, t);
	else if (r < (accumulator += DERAUMERE_CHANCE))
		place_stone(DERAUMERE, t);
	else if (r < (accumulator += SIBUR_CHANCE))
		place_stone(SIBUR, t);
	else if (r < (accumulator += MENDIANE_CHANCE))
		place_stone(MENDIANE, t);
	else if (r < (accumulator += PHIRAS_CHANCE))
		place_stone(PHIRAS, t);
	else
		place_stone(THYSTAME, t);
}

void	do_per_tick_resource_generation(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_map->dim.x)
	{
		j = 0;
		while (j < g_map->dim.y)
		{
			if (random() % SPAWN_CHANCE_DENOMINATOR < SPAWN_CHANCE_NUMERATOR)
				spawn_random_resource_on_tile(&g_map->tile[i][j]);
			++j;
		}
		++i;
	}
}

void	seed_tiles_initial_resources(void)
{
	int		i;

	i = 0;
	while (i < PREGAME_RESOURCE_SPAWNING_ROUNDS)
	{
		do_per_tick_resource_generation();
		++i;
	}
}
