#include "server.h"
#include "player_type.h"

char	*inventory(int player_id, void *args)
{
	char		*str;
	t_player	*p;

	(void)args;
	p = get_player(player_id);
	asprintf(&str, "{food %d, linemate %d, deraumere %d, \
sibur %d, mendiane %d, phiras %d, thystame %d}\n",
			p->count[FOOD] * ENERGY_PER_FOOD + p->energy,
			p->count[LINEMATE],
			p->count[DERAUMERE],
			p->count[SIBUR],
			p->count[MENDIANE],
			p->count[PHIRAS],
			p->count[THYSTAME]);
	gfx_sendall("INVENTORY %d\n", player_id);
	return (str);
}
