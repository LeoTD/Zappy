#ifndef CLIENT_TYPE_H
# define CLIENT_TYPE_H
# include "command_queue_type.h"

struct s_client
{
	int				socket_fd;
	int				player_id;
	t_command_queue	*cmdqueue;
};
#endif
