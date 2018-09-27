#ifndef CLIENT_TYPE_H
# define CLIENT_TYPE_H
# include "server.h"
# include "command_player_queue_type.h"

enum	e_client_types
{
	PLAYER_CLIENT,
	GFX_CLIENT
};

struct	s_client
{
	int					socket_fd;
	int					id;
	int					type;
	t_ply_cmd_queue		cmdqueue;
};

#endif
