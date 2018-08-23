#include "server.h"

/*
**	Takes the food and resources and displays them in a nice format delimited by
**	spaces, and enclosed by brackets.
**	May or may not convert food to energy.
*/

char	*inventory(int player_id, void *args)
{
	char	*str;
	
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return ("placeholder inventory response\n");
//	str = get_player_inventory(player_id);
//	return (str);
}
