#ifndef SERVER_H
# define SERVER_H
# include "client_type.h"
# include "cmdfunc_type.h"
# include "command_list_type.h"
# include "command_queue_type.h"
# include "command_type.h"
# include <stdio.h>

# define FATAL(msg) ({ fprintf(stderr, "%s: %s\n", __func__, msg); exit(-1); })

enum			e_connection_type
{
	HANDSHAKE,
	USER,
	SERVER,
	GFX
};

typedef void	(*t_cmdfunc)(int player_id, void *args);

typedef struct	s_command
{
	t_cmdfunc	cmdfunc;
	char		*args;
	char		*response;
	int			player_id;
}				t_command;

typedef struct	s_command_list
{
	t_command	*cmd;
	t_command	*next;
}				t_command_list;

typedef struct	s_command_queue
{
	t_command_list	*head;
	t_command_list	*tail;
	int				remaining_space;
	int				dequeue_timer;
}				t_command_queue;

typedef struct	s_client
{
	int				socket_fd;
	int				player_id;
	t_command_queue	*cmdqueue;
}				t_client;

void			listen_for_connections(int port);

#endif
