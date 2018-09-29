#include "server.h"
#include "tile_type.h"
#include "player_type.h"

char				*fork_player(int player_id, void *args)
{
	t_player		*p;

	(void)args;
	p = get_player(player_id);
	enqueue_player_egg(p->tile->x, p->tile->y, p->team_id);
	gfx_sendall("DONE_LAYING_EGG %d %d %d %d\n",
			p->id, p->team_id, p->tile->x, p->tile->y);
	return (ok_response());
}
