#include "server.h"
#include "player_type.h"
#include "tile_type.h"
#include "client_type.h"

/*
**	Remove_pid searches through the array, removes the `current` passed in pid
**	and returns a realloced array without the pid.
*/

int		*remove_pid(int *parray, int size, int current)
{
	int		i;
	int		*copy;

	i = 0;
	size = size - 1;
	copy = realloc(parray, size);
	while (i < size)
	{
		if (parray[i] != current)
			copy[i] = parray[i];
		i++;
	}
	free(parray);
	return (copy);
}

char	*find_kick_origin(int kick_dir, int player_dir)
{
	char	*str;
	char	*k;

	str = strnew("moving ");
	if (facing_same(kick_dir, player_dir))
		k = strnew("<5>\n");
	else if (facing_opposite(kick_dir, player_dir))
		k = strnew("<1>\n");
	else if (kicked_from_left(kick_dir, player_dir))
		k = strnew("<3>\n");
	else if (kicked_from_right(kick_dir, player_dir))
		k = strnew("<7>\n");
	else
		k = strnew("<?>\n");
	str = strjoin_free(str, k);
	return (str);
}

/*
**	Kick_em takes an array of pids, the size of the array, and the direction that 
**	they will be moving. Moves all pids that direction.
**	May or may not segfault here.
*/

void	kick_em(int *parray, int dir, int size, int kpid)
{
	char			*msg;
	t_client		*client;
	t_player		*player;
	
	while (size > 0)
	{
		player = get_player(parray[size - 1]);
		if (player->id != kpid)
		{
			assert(client = get_client_by_player_id(player->id));
			msg = find_kick_origin(dir, player->facing);
			send(client->socket_fd, msg, strlen(msg), 0);
			move_player(player, dir);
		}
		size--;
	}
}

/*
**	Checks to see if number of players is greater than 1. If not, return error 1.
**	If they are other players. Grab all players on current tile minus the player kicking
**	and move all players the direction the kicking player is facing.
*/

void	print_parray(int *parray, int size)
{
	int i = 0;

	while (i < size)
		printf("the parray is: |%d|\n", parray[i++]);
}

int		attempt_to_kick(int pid)
{
	int			size;
	int			*parray;
	t_player	*player;

	player = get_player(pid);
	if (player->tile->num_players <= 1)
		return (-1);
	parray = get_current_tile_player_count(pid, &size);
//	print_parray(parray, size);
//	printf("size = %d\n", size);
	kick_em(parray, player->facing, size, pid);
	free(parray);
	return (0);
}
