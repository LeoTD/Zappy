#include "server.h"
#include "player_type.h"
#include "tile_type.h"

t_tile		*iter_tiles(void)
{
	static int prev_x = 0;
	static int prev_y = -1;
	int		x;
	int		y;

	if (prev_x == g_map->dim.x - 1 && prev_y == g_map->dim.y - 1)
	{
		prev_x = 0;
		prev_y = -1;
		return (NULL);
	}
	else if (prev_y == g_map->dim.y - 1)
	{
		x = prev_x + 1;
		y = 0;
	}
	else
	{
		x = prev_x;
		y = prev_y + 1;
	}
	prev_y = y;
	prev_x = x;
	return (&g_map->tile[x][y]);
}

t_player	*iter_players(void)
{
	static int found_players = -1;
	static int last_found_player_id = -1;
	t_player	*p;
	int			pid;

	if (found_players == g_map->players)
	{
		found_players = -1;
		return (NULL);
	}
	if (found_players == -1)
	{
		found_players = 0;
		last_found_player_id = -1;
	}
	pid = last_found_player_id + 1;
	while ((p = get_player(pid)) == NULL)
		pid++;
	found_players++;
	last_found_player_id = pid;
	return (p);
}
