#include "server.h"
#include "client_type.h"
#include "command_queue_type.h"

void	decrement_user_command_timers(t_client **clients)
{
	int		i;

	i = 0;
	while (clients[i])
	{
		if (clients[i]->type == ACTIVE_PLAYER
				&& clients[i]->cmdqueue.dequeue_timer > 0)
		{
			clients[i]->cmdqueue.dequeue_timer -= 1;
		}
		++i;
	}
}
