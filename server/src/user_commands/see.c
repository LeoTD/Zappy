#include "server.h"

/*
**	We get the player, and the player's level.
**	Based on the player's level, a player can see a certain range
**	of tiles. 
*/

char	*see(int player_id, void *args)
{
	char	*response = "placeholder";

	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	//response = see_tiles(player_id);
	return (response);	
}
