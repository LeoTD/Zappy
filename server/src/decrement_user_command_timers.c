#include "server.h"
#include "client_type.h"
#include "command_player_queue_type.h"

void	decrement_user_command_timers(void)
{
	t_client	*c;

	while ((c = iter_clients(ACTIVE_PLAYER)))
	{
		if (c->cmdqueue.dequeue_timer > 0)
			c->cmdqueue.dequeue_timer -= 1;
	}
}
