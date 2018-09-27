#include "server.h"

char	*put(int player_id, void *args)
{
	char		*obj_to_put;

	obj_to_put = (char*)args;
	if (attempt_to_put(player_id, obj_to_put))
	{
		return (ko_response());
	}
	return (ok_response());
}
