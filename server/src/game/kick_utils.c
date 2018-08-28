#include "server.h"

char	facing_same(int kick_dir, int player_dir)
{
	if (kick_dir == player_dir)
		return (1);
	return (0);
}

char	facing_opposite(int kick_dir, int player_dir)
{
	if (kick_dir == NORTH && player_dir == SOUTH)
		return (1);
	if (kick_dir == EAST && player_dir == WEST)
		return (1);
	if (kick_dir == WEST && player_dir == EAST)
		return (1);
	if (kick_dir == SOUTH && player_dir == NORTH)
		return (1);
	return (0);
}

char	kicked_from_left(int kick_dir, int player_dir)
{
	if (kick_dir == NORTH && player_dir == WEST)
		return (1);
	if (kick_dir == EAST && player_dir == NORTH)
		return (1);
	if (kick_dir == WEST && player_dir == SOUTH)
		return (1);
	if (kick_dir == SOUTH && player_dir == EAST)
		return (1);
	return (0);
}

char	kicked_from_right(int kick_dir, int player_dir)
{
	if (kick_dir == NORTH && player_dir == EAST)
		return (1);
	if (kick_dir == EAST && player_dir == SOUTH)
		return (1);
	if (kick_dir == WEST && player_dir == NORTH)
		return (1);
	if (kick_dir == SOUTH && player_dir == WEST)
		return (1);
	return (0);
}
