
#include "server.h"

t_tile			*get_adj_tile(t_tile *home, int dir)
{
	if (dir == NORTH)
		return (get_tile_NS(home, -1));
	else if (dir == SOUTH)
		return (get_tile_NS(home, 1));
	else if (dir == EAST)
		return (get_tile_EW(home, 1));
	else if (dir == WEST)
		return (get_tile_EW(home, -1));
	if (dir == NORTHEAST)
		return (get_tile_EW(get_tile_NS(home, -1), 1));
	if (dir == NORTHWEST)
		return (get_tile_EW(get_tile_NS(home, -1), -1));
	if (dir == SOUTHEAST)
		return (get_tile_EW(get_tile_NS(home, 1), 1));
	if (dir == SOUTHWEST)
		return (get_tile_EW(get_tile_NS(home, 1), -1));
	return (NULL);
}

/*
** Takes [ int v(ector) ]
** (0, 0) is the NORTHWEST corner of the map.
**
** So, +1 moves one tile SOUTH. -1 moves on tile NORTH.
** This is not limited to increments of 1, however the common use will
** move one tile at a time.
**
** EAST-WEST funciton works similarly.
*/

t_tile			*get_tile_NS(t_tile *home, int v)
{
	int			newy;

	if (abs(v) > g_map->dim.y)
		v = v % g_map->dim.y;
	newy = home->y;
	newy += v;
	if (newy >= g_map->dim.y)
		newy = newy - g_map->dim.y;
	else if (newy < 0)
		newy = newy + g_map->dim.y;
	return (&g_map->tile[home->x][newy]);
}

t_tile			*get_tile_EW(t_tile *home, int v)
{
	int			newx;

	if (abs(v) > g_map->dim.x)
		v = v % g_map->dim.x;
	newx = home->x;
	newx += v;
	if (newx >= g_map->dim.x)
		newx = newx - g_map->dim.x;
	else if (newx < 0)
		newx = newx + g_map->dim.x;
	return (&g_map->tile[newx][home->y]);
}
