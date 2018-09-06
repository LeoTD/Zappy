#include "server.h"

char	*connect_nbr(int player_id, void *args)
{
	char		*res;

	asprintf(&res, "%d", get_team_open_slots_by_pid(player_id));
	printf("p%d: %s(%s)\n", player_id, __func__, args ? (char *)args : "");
	return (res);
}