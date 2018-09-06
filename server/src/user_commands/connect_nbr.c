#include "server.h"

char	*connect_nbr(int player_id, void *args)
{
	char		*res;

	asprintf(&res, "%d\n", get_team_open_slots_by_pid(player_id));
	return (res);
}