#ifndef COMMAND_QUEUE_TYPE_H
# define COMMAND_QUEUE_TYPE_H
# include "server.h"

t_command_queue		*new_cmdqueue(void);
void				free_cmdqueue(t_command_queue *q);
int					enqueue_command(t_command_queue *q, t_command *cmd);
t_command_list		*dequeue_command(t_command_queue *q);

#endif
