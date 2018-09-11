#include "server.h"
#include "player_type.h"

void        feed_players(void)
{
    int         fed;
	int			pid;
    t_player    *p;

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
					kill_player(p);
			}
			fed++;
		}
		pid++;
    }
}

void        game_upkeep(void)
{
    reset_obituary();
	feed_players();
	do_per_tick_resource_generation();
}
