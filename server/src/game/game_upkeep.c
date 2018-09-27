#include "server.h"
#include "player_type.h"

void	feed_players(void)
{
	t_player	*p;

	while ((p = iter_players()))
	{
		p->energy--;
		if (p->energy <= 0 && p->count[FOOD] > 0)
		{
			p->count[FOOD]--;
			p->energy = ENERGY_PER_FOOD;
		}
		else if (p->energy <= 0)
			mark_player_for_death(p);
	}
}

void	game_upkeep(void)
{
	feed_players();
	do_per_tick_resource_generation();
}
