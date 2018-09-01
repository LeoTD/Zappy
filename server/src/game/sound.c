#include "server.h"
#include "tile_type.h"
#include "player_type.h"

int		sound_came_from_diagonal(int x, int y)
{
	if (x > 0)
	{
		if (x == y)
			return (8); // top right
		if (x == -y)
			return (6); // bottom right
	}
	if (x < 0)
	{
		if (x == y)
			return (4); // bottom left
		if (x == -y)
			return (2); // top right
	}
	return (-1);
}

int		sound_came_from_cardinal(int x, int y)
{
	if (x == 0)
	{
		if (y > 0)
			return (1); // top
		return (5); // bottom
	}
	else if (y == 0)
	{
		if (x > 0)
			return (7); // right
		return (3); // left
	}
	return (-1);
}

int		origin_center(int x, int y)
{
	if (x == 0 && y == 0) // same square
		return (0);
	return (-1);
}

int		find_sound_direction(int x, int y)
{
	int		i;
	if ((i = origin_center(x, y)) != -1)
		return (0);
	if ((i = sound_came_from_cardinal(x, y)) != -1)
		return (i);
	if ((i = sound_came_from_diagonal(x, y)) != -1)
		return (i);
	printf("Error sound.c: find_sound_direction\n");
	return (-1);
}
