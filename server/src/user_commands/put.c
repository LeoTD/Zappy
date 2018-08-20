#include "server.h"

char	*put(int player_id, void *args)
{
	char		*obj_to_put;

	(void)args;
	obj_to_put = (char*)args;
	if (attempt_to_put(player_id, obj_to_put))
	{
		return ("ko\n");
	}
	return ("ok\n");
}
