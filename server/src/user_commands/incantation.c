#include "server.h"

char	*incantation(int player_id, void *args)
{
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return "placeholder incantation response\n";
}
