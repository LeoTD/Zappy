#include "server.h"
#include "player_type.h"
#include "tile_type.h"

/*
**	Kick_em takes an array of pids, the size of the array, and the direction that 
**	they will be moving. Moves all pids that direction.
**	May or may not segfault here.
*/

void	kick_em(int *parray, int dir, int size, int kpid)
{
	t_player	*player;
	
	while (size > 0)
	{
		player = get_player(parray[size - 1]);
		if (player->id != kpid)
			move_player(player, dir);
		size--;
	}
	write(1, "segfault warning\n", 17);
}

/*
**	Checks to see if number of players is greater than 1. If not, return error 1.
**	If they are other players. Grab all players on current tile minus the player kicking
**	and move all players the direction the kicking player is facing.
*/

int		attempt_to_kick(int pid)
{
	int			size;
	int			*parray;
	t_player	*player;

	player = get_player(pid);
	if (player->tile->num_players <= 1)
		return (-1);
	parray = get_current_tile_player_count(pid, &size);
	kick_em(parray, player->facing, size, pid);
	free(parray);
	return (0);
}
