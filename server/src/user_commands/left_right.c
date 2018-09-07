#include "server.h"
#include "player_type.h"

char	*left(int player_id, void *args)
{
	t_player	*p;

	(void)args;
	p = get_player(player_id);
	p->facing = direction_add(p->facing, WEST);
	return ("ok\n");
}

char	*right(int player_id, void *args)
{
	t_player	*p;

	(void)args;
	p = get_player(player_id);
	p->facing = direction_add(p->facing, EAST);
	return ("ok\n");
}
