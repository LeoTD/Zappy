#include "server.h"

/*
**	Takes the food and resources and displays them in a nice format delimited by
**	spaces, and enclosed by brackets.
**	May or may not convert food to energy.
*/

char	*inventory(int player_id, void *args)
{
	char	*str;

	str = get_player_inventory(player_id);
	return (str);
}
