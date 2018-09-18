#include "server.h"
#include "player_type.h"
#include "client_type.h"

char	*kick_origin_message(int kick_dir, t_player *p)
{
	static char msg[] = "moving <K>\n";

	msg[8] = '0' + perceived_direction(opposite_direction(kick_dir), p);
	return (msg);
}

void	kick_and_alert_player(t_player *p, int dir)
{
	t_client	*client;
	char		*msg;

	move_player(p, dir);
	gfx_sendall("GET_KICKED %d %d\n", p->id, dir);
	if ((client = get_client_by_id(p->id)))
	{
		msg = kick_origin_message(dir, p);
		send(client->socket_fd, msg, strlen(msg), 0);
	}
}

char	*kick(int player_id, void *args)
{
	int			*tile_pids;
	int			kick_dir;
	int			npids;
	int			i;

	(void)args;
	tile_pids = get_current_tile_player_count(player_id, &npids);
	kick_dir = get_player(player_id)->facing;
	gfx_sendall("KICK %d %d %d\n", player_id, kick_dir, npids - 1);
	i = 0;
	while (i < npids)
	{
		if (tile_pids[i] != player_id)
			kick_and_alert_player(get_player(tile_pids[i]), kick_dir);
		i++;
	}
	free(tile_pids);
	gfx_sendall("%s", "DONE\n");
	return (npids > 1 ? "ok\n" : "ko\n");
}
