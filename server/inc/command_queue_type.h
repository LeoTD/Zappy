#ifndef COMMAND_QUEUE_TYPE_H
# define COMMAND_QUEUE_TYPE_H
# include "server.h"
# include "command_list_type.h"

struct	s_command_queue
{
	t_command_list	*head;
	t_command_list	*tail;
	int				remaining_space;
	int				dequeue_timer;
};

#endif
