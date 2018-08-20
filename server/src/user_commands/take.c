#include "server.h"

char	*take(int player_id, void *args)
{
	char		*obj_to_take;

	(void)args;
	obj_to_take = (char*)args;
	if (attempt_to_take(player_id, obj_to_take))
	{
		return ("ko\n");
	}
	return ("ok\n");
}
