#include "client_type.h"
#include "player_type.h"
#include "tile_type.h"
#include "command_queue_type.h" 

t_player	*client_controlled_player_on_tile(t_tile *t)
{
	t_player *p;
	t_client *c;

	for (int i = 0; i < t->count[PLAYERS]; i++)
		if ((p = t->players[i]) && (c = get_client_by_id(p->id)) && c->type == ACTIVE_PLAYER)
			return (p);
	return (NULL);
}

void		print_player_facing(t_player *p)
{
	printf("%c ", ((char []){ [NORTH] = '^', [EAST] = '>', [SOUTH] = 'v' , [WEST] = '<'}[p->facing]));
}

void			print_tile(t_tile *t)
{
	t_player	*p;

	if (t->count[PLAYERS] == 0)
		printf(". ");
	else if ((p = client_controlled_player_on_tile(t)))
		print_player_facing(p);
	else if (t->count[PLAYERS] <= 9)
		printf("%d ", t->count[PLAYERS]);
	else
		printf("? ");
}

void			animate(void)
{
	static int ticks = 0;

#ifdef ASCII_ANIMATIONS
	system("clear");
	printf("[0-9] = num empty bodies, (? if > 9), >^<v = connected client\n\n");
	printf("x = %d, y = %d. port = %d. tick %d\n", g_map->dim.x, g_map->dim.y, g_opts.server_port, ticks);
	for (int row = 0; row < g_map->dim.y; row++)
	{
		for (int col = 0; col < g_map->dim.x; col++)
		{
			t_tile *t = &g_map->tile[col][row];
			print_tile(t);
		}
		printf("\n");
	}
#else
	if (ticks == 0)
		printf("each . = 126 ticks, or | for 1260. server port = %d\n", g_opts.server_port);
	else if (ticks % 126 == 0)
	{
		if (ticks % 1260 == 0)
			printf("|");
		else
			printf(".");
	}
	fflush(stdout);
#endif
	++ticks;
}
