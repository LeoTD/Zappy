#ifndef COMMAND_QUEUE_TYPE_H
# define COMMAND_QUEUE_TYPE_H
# include "server.h"

typedef struct		s_command_queue
{
	t_command_list	*head;
	t_command_list	*tail;
	int				remaining_space;
	int				dequeue_timer;
}					t_command_queue;


t_command_queue		*new_cmdqueue(void);
void				free_cmdqueue(t_command_queue *q);
int					enqueue_command(t_command_queue *q, t_command *cmd);
t_command_list		*dequeue_command(t_command_queue *q);

#endif
