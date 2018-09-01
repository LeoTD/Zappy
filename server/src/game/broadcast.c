#include "server.h"
#include "tile_type.h"
#include "player_type.h"
#include "client_type.h"
/*
**	Start from the player's starting square, find all other players
**	And where they should recieve the message from (direction).
**	First, we need to find the square that is adjacent to the player.
**	Then, decide which relative position to that square is.
**	Combine msg + relative position to send to player.
**	Repeat for all players.
*/

//	Something that finds the distance, either direct distance or wrap around distance
//	(x2 - x1) or (0 - x1 + x2 - map_width)
//	(y2 - y1) or (0 - y1 + x2 - map_width)

char	*get_direction(int pid, int *origin);

void	send_msg(char *msg, int msg_len, t_client *cli, int *origin)
{
	char		*msg_and_dir;
	t_player	*p;

	p = get_player(cli->player_id);
	msg_and_dir = strjoin_free(msg, get_direction(cli->player_id, origin));
	send(cli->socket_fd, msg_and_dir, msg_len + 3, 0);
	free(msg_and_dir);
}

void	send_broadcast(int player_id, char *msg)
{
	int			i;
	int			msg_len;
	int			origin[2];
	t_player 	*player;
	t_client	**clients;

	player = get_player(player_id);
	origin[0] = player->tile->x;
	origin[1] = player->tile->y;
	clients = get_clients();
	i = 0;
	msg_len = strlen(msg);
	while (clients[i])
	{
		send_msg(msg, msg_len, clients[i], origin);
		i++;
	}
}
