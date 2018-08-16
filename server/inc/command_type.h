#include "server.h"

struct s_command
{
	t_cmdfunc	cmdfunc;
	char		*args;
	char		*response;
	int			player_id;
};
