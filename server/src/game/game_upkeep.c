#include "server.h"
#include "player_type.h"

void	feed_players(void)
{
	int			fed;
	int			pid;
	t_player	*p;

	fed = 0;
	pid = 0;
	while (fed < g_map->players)
	{
		if ((p = get_player(pid)) != NULL)
		{
			p->energy--;
			if (p->energy <= 0)
			{
				if (p->count[FOOD] > 0)
				{
					p->count[FOOD]--;
					p->energy += ENERGY_PER_FOOD;
				}
				else
				{
					printf("%d ", fed);
					printf("%d\n", p->id);
					kill_player(p);
					pid++;
					continue;
				}
			}
			fed++;
		}
//		fed++;
		pid++;
	}
//	printf("BREAK\n");
}

void	game_upkeep(void)
{
	reset_obituary();
	feed_players();
	do_per_tick_resource_generation();
}
