#include "server.h"

int			game_init(int x, int y, int teams, int players)
{
	int			i;
	int			j;

	i = -1;
	j = -1;
	if ((g_map = malloc(sizeof(t_game_info))) == NULL)
		ERR_OUT("game_init; malloc");
	g_map->x = x;
	g_map->y = y;
	create_map(x, y);
	g_map->teams = teams;
	if ((g_map->empty_avatars = 
				malloc(sizeof(t_plist *) * (teams + 1))) == NULL)
		ERR_OUT("game_init->empty_avatars; malloc");
	bzero(g_map->empty_avatars, sizeof(t_plist *) * (teams + 1));
	while (++i < teams)
	{
		while (++j < players)
			new_player(EGG_TIMER, i, j);
		j = -1;
	}
}
