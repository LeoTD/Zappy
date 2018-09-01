#include "server.h"
#include "tile_type.h"
#include "player_type.h"

int		x_dist(int x1, int x2)
{
	int		x;
	int		map_x = 0;

	x = x2 - x1;
	return (x <= map_x / 2) ? x : x - map_x; // -1
}

int		y_dist(int y1, int y2)
{
	int		y;
	int		map_y = 0;

	y = y2 - y1;
	return (y <= map_y / 2) ? y : y - map_y; // -1
}

void	find_distance(t_tile *tile, int *origin, int *x, int *y)
{
	*x = x_dist(origin[0], tile->x);
	*y = y_dist(origin[1], tile->y);
}

char	*get_direction(int pid, int *origin)
{
	int			x;
	int			y;
	char		*result;
	int			direction;
	t_player	*player;

	player = get_player(pid);
	find_distance(player->tile, origin, &x, &y);
	direction = find_sound_direction(x, y);
	direction = get_relative_direction(pid, direction);
	result = strnew("...");
	result[0] = ' ';
	result[1] = (char)direction;
	result[2] = '\n';
	return (result);
}
