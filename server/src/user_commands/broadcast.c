#include "server.h"

char	*broadcast(int player_id, void *args)
{
	send_broadcast(player_id, (char*)args);
	return ("ok\n");
}
