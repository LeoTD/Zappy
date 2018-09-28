#ifndef COMMAND_TYPE_H
# define COMMAND_TYPE_H
# include "server.h"

struct	s_command
{
	t_cmdfunc	cmdfunc;
	char		*args;
	char		*response;
	int			player_id;
};

#endif
