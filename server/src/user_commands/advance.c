#include "server.h"
#include "player_type.h"

char	*advance(int player_id, void *args)
{
	t_player	*player;

	(void)args;
	player = get_player(player_id);
	move_player(player, player->facing);
	gfx_sendall("ADVANCE %d\n", player->id);
	return ("ok\n");
}
