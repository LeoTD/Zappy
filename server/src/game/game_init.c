#include "server.h"
#include "tile_type.h"

t_tile		*get_random_tile(void)
{
	int			rx;
	int			ry;

	rx = random() % g_map->dim.x;
	ry = random() % g_map->dim.y;
	return (&g_map->tile[rx][ry]);
}

void		randomize_player_positions(void)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	j = -1;
	k = -1;
	while (++i < g_map->teams)
	{
	}
}

int			game_init(int x, int y, int teams, int players)
{
	int			i;
	int			j;

	i = -1;
	j = -1;
	if ((g_map = malloc(sizeof(t_game_info))) == NULL)
		ERR_OUT("game_init; malloc");
	g_map->dim.x = x;
	g_map->dim.y = y;
	create_map(x, y);
	g_map->teams = teams;
	if ((g_map->empty_avatars = 
				malloc(sizeof(t_plist *) * (teams + 1))) == NULL)
		ERR_OUT("game_init->empty_avatars; malloc");
	bzero(g_map->empty_avatars, sizeof(t_plist *) * (teams + 1));
	if ((g_map->players_on_team = malloc(sizeof(int) * teams)) == NULL)
		ERR_OUT("game_init->players_on_team; malloc");
	while (++i < teams)
	{
		while (++j < players)
			new_player(EGG_TIMER, i, j);
		j = -1;
		g_map->players_on_team[i] = players;
	}
	randomize_player_positions();
	return (0);
}
